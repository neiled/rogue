#include "shadowcasting.h"

ShadowCasting::ShadowCasting()
{
}

ShadowCasting::~ShadowCasting()
{
}

std::vector<std::vector<float>>  ShadowCasting::calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float radius) {
  return calculateFOV(resistanceMap, startx, starty, 1.0, 1.0 /radius);
}
std::vector<std::vector<float>>  ShadowCasting::calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float force, float decay) {
    _startx = startx;
    _starty = starty;
 
    _width = resistanceMap.size();
    _height = resistanceMap[0].size();

    _radius = force/decay;
    _force = force;
    _decay = decay;
    //SDL_Log("Radius: %f, force: %f", _radius, _force);

    _lightMap.resize(_height);
    for (int i = 0; i < _height; ++i)
    {
      _lightMap[i].resize(_width, 0);
    }
 
    _lightMap[starty][startx] = force;
    //for (Direction d : Direction.DIAGONALS) {
    for (int i = -1; i < 2; i+=2)
    {
      for (int j = -1; j < 2; j+=2)
      {
        
        castLight(1, 1.0f, 0.0f, 0, i, j, 0, resistanceMap);
        castLight(1, 1.0f, 0.0f, i, 0, 0, j, resistanceMap);
      }
      
    }
    //}
 
    return _lightMap;
}

float ShadowCasting::radius(float dx, float dy)
{
  return sqrt(dx*dx+dy*dy);
}
 
void ShadowCasting::castLight(int row, float start, float end, int xx, int xy, int yx, int yy, resistance_map_t resistance_map) {
    float newStart = 0.0f;
    if (start < end) {
        return;
    }
    bool blocked = false;
    for (int distance = row; distance <= _radius && !blocked; distance++) {
        int deltaY = -distance;
        for (int deltaX = -distance; deltaX <= 0; deltaX++) {
            int currentX = _startx + deltaX * xx + deltaY * xy;
            int currentY = _starty + deltaX * yx + deltaY * yy;
            float leftSlope = (deltaX - 0.5f) / (deltaY + 0.5f);
            float rightSlope = (deltaX + 0.5f) / (deltaY - 0.5f);
 
            if (!(currentX >= 0 && currentY >= 0 && currentX < _width && currentY < _height) || start < rightSlope) {
                continue;
            } else if (end > leftSlope) {
                break;
            }
 
            //check if it's within the lightable area and light if needed
            if (radius(deltaX, deltaY) <= _radius) {
                float bright = (float) (1 - (_decay * radius(deltaX, deltaY) / _force));

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
                if (blockingCell(resistance_map[currentY][currentX]) && distance < _radius) {//hit a wall within sight line
                    blocked = true;
                    castLight(distance + 1, start, leftSlope, xx, xy, yx, yy, resistance_map);
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
  if(tile->tile_type() == TileType::Door)
    return true;
  return false;
}
