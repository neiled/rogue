#ifndef SHADOW_H
#define SHADOW_H 

#include <array>
#include <vector>
#include "level.h"

class Tile;

typedef std::array<std::array<Tile*, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT> resistance_map_t;
class ShadowCasting
{
public:
    ShadowCasting ();
    virtual ~ShadowCasting ();
    std::vector<std::vector<float>> calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float force, float decay);
    std::vector<std::vector<float>> calculateFOV(resistance_map_t resistanceMap, int startx, int starty, float radius);
    bool blockingCell(Tile* tile);

private:
    int _width;
    int _height;
    std::vector<std::vector<float> > _lightMap;
    std::vector<std::vector<float> > _visimap;

    void castLightAllDirections(int row, float start, float end, int startx, int starty, resistance_map_t resistance_map,
                                float force, float decay);

    void
    checkVisibilityAllDirections(int row, float start, float end, int startx, int starty, resistance_map_t resistance_map,
                                 float decay, float force);

    void castLight(int row, float start, float end, int startx, int starty, int xx, int xy, int yx, int yy,
                   resistance_map_t resistance_map, float force, float decay);

    void setVisibility(int row, float start, float end, int startx, int starty, int xx, int xy, int yx, int yy,
                       resistance_map_t resistance_map, float decay, float force);

    float getRadius(float dx, float dy);
};
#endif
