#include "shadowcasting.h"

ShadowCasting::ShadowCasting()
{
}

ShadowCasting::~ShadowCasting()
{
}

//TODO: This needs to become 'add lights' and will take in the level and generate lights based on player and/or light sources in the level
std::vector<std::vector<float>>  ShadowCasting::calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float radius) {
  return calculateFOV(resistanceMap, startx, starty, 1.0, 1.0 /radius);
}
std::vector<std::vector<float>>  ShadowCasting::calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float force, float decay) {

    _width = resistanceMap.size();
    _height = resistanceMap[0].size();


    _lightMap.resize(_height);
    _visimap.resize(_height);
    for (int i = 0; i < _height; ++i)
    {
        _lightMap[i].resize(_width, 0);
        _visimap[i].resize(_width, 0);
    }
 
    _lightMap[starty][startx] = force;

    castLightAllDirections(1, 1.0f, 0.0f, startx, starty, resistanceMap, force, decay);


    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            auto tile = resistanceMap[y][x];
            if(tile->tile_type() == TileType::Door)
            {
                _lightMap[tile->y()][tile->x()] = force;
                castLightAllDirections(1, 1.0f, 0.0f, tile->x(), tile->y(), resistanceMap, force, decay);
            }
        }
    }

    checkVisibilityAllDirections(1, 1.0, 0.0f, startx, starty, resistanceMap, force, decay);

    return _lightMap;
}

void ShadowCasting::castLightAllDirections(int row, float start, float end, int startx, int starty, resistance_map_t resistance_map, float force, float decay)
{
    for (int i = -1; i < 2; i+=2)
    {
        for (int j = -1; j < 2; j+=2)
        {

            castLight(row, start, end, startx, starty, 0, i, j, 0, resistance_map, force, decay);
            castLight(row, start, end, startx, starty, i, 0, 0, j, resistance_map, force, decay);
        }

    }

}

void ShadowCasting::checkVisibilityAllDirections(int row, float start, float end, int startx, int starty, resistance_map_t resistance_map, float force, float decay)
{
    for (int i = -1; i < 2; i+=2)
    {
        for (int j = -1; j < 2; j+=2)
        {

            setVisibility(row, start, end, startx, starty, 0, i, j, 0, resistance_map, force, decay);
            setVisibility(row, start, end, startx, starty, i, 0, 0, j, resistance_map, force, decay);
        }

    }

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            _lightMap[y][x] = _visimap[y][x] < 1.0 ? 0.0f : _lightMap[y][x];
        }
    }

}
float ShadowCasting::getRadius(float dx, float dy)
{
  return (float) sqrt(dx * dx + dy * dy);
}

void ShadowCasting::setVisibility(int row, float start, float end, int startx, int starty, int xx, int xy, int yx, int yy, resistance_map_t resistance_map, float force, float decay) {
    auto radius = force/decay;
    float newStart = 0.0f;
    if (start < end) {
        return;
    }
    bool blocked = false;
    for (int distance = row; distance <= radius && !blocked; distance++) {
        int deltaY = -distance;
        for (int deltaX = -distance; deltaX <= 0; deltaX++) {
            int currentX = startx + deltaX * xx + deltaY * xy;
            int currentY = starty + deltaX * yx + deltaY * yy;
            float leftSlope = (deltaX - 0.5f) / (deltaY + 0.5f);
            float rightSlope = (deltaX + 0.5f) / (deltaY - 0.5f);

            if (!(currentX >= 0 && currentY >= 0 && currentX < _width && currentY < _height) || start < rightSlope) {
                continue;
            } else if (end > leftSlope) {
                break;
            }

            //check if it's within the lightable area and light if needed
            if (getRadius(deltaX, deltaY) <= radius) {
                float bright = 1 - (decay * getRadius(deltaX, deltaY) / force);

                if(bright > 0)
                _visimap[currentY][currentX] = 1;
            }

            if (blocked) { //previous cell was a blocking one
                if (blockingCell(resistance_map[currentY][currentX])) {//hit a wall
                    newStart = rightSlope;
                    continue;
                } else {
                    blocked = false;
                    start = newStart;
                }
            } else {
                if (blockingCell(resistance_map[currentY][currentX]) && distance < radius) {//hit a wall within sight line
                    blocked = true;
                    setVisibility(distance + 1, start, leftSlope, startx, starty, xx, xy, yx, yy, resistance_map, force, decay);
                    newStart = rightSlope;
                }
            }
        }
    }
}


void ShadowCasting::castLight(int row, float start, float end, int startx, int starty, int xx, int xy, int yx, int yy, resistance_map_t resistance_map, float force, float decay) {
    auto radius = force/decay;
    float newStart = 0.0f;
    if (start < end) {
        return;
    }
    bool blocked = false;
    for (int distance = row; distance <= radius && !blocked; distance++) {
        int deltaY = -distance;
        for (int deltaX = -distance; deltaX <= 0; deltaX++) {
            int currentX = startx + deltaX * xx + deltaY * xy;
            int currentY = starty + deltaX * yx + deltaY * yy;
            float leftSlope = (deltaX - 0.5f) / (deltaY + 0.5f);
            float rightSlope = (deltaX + 0.5f) / (deltaY - 0.5f);

            if (!(currentX >= 0 && currentY >= 0 && currentX < _width && currentY < _height) || start < rightSlope) {
                continue;
            } else if (end > leftSlope) {
                break;
            }

            //check if it's within the lightable area and light if needed
            if (getRadius(deltaX, deltaY) <= radius) {
                float bright = 1 - (decay * getRadius(deltaX, deltaY) / force);

                _lightMap[currentY][currentX] = bright;
            }

            if (blocked) { //previous cell was a blocking one
                if (blockingCell(resistance_map[currentY][currentX])) {//hit a wall
                    newStart = rightSlope;
                    continue;
                } else {
                    blocked = false;
                    start = newStart;
                }
            } else {
                if (blockingCell(resistance_map[currentY][currentX]) && distance < radius) {//hit a wall within sight line
                    blocked = true;
                    castLight(distance + 1, start, leftSlope, startx, starty, xx, xy, yx, yy, resistance_map, force, decay);
                    newStart = rightSlope;
                }
            }
        }
    }
}
bool ShadowCasting::blockingCell(Tile* tile)
{
  if(tile->tile_type() == TileType::Rock)
    return true;
    return tile->tile_type() == TileType::Door;
}
