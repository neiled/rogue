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
    //  void castLight(int row, float start, float end, int xx, int xy, int yx, int yy, resistance_map_t resistance_map);
    float radius(float dx, float dy);
    bool blockingCell(Tile* tile);

private:
//  int _startx;
//  int _starty;
    float _radius;
    float _force;
    float _decay;
    //std::array<std::array<std::shared_ptr<Tile>, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _resistanceMap;
    //std::array<std::array<Tile&, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT> _resistanceMap;
    int _width;
    int _height;
    std::vector<std::vector<float> > _lightMap;

    void castLight(int row, float start, float end, int startx, int starty, int xx, int xy, int yx, int yy,
                   resistance_map_t resistance_map);
};
#endif
