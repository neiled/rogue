#ifndef SHADOW_H
#define SHADOW_H 

#include <array>
#include <vector>
#include "level.h"

class Tile;

class ShadowCasting
{
public:
  ShadowCasting ();
  virtual ~ShadowCasting ();
  std::vector<std::vector<float>> calculateFOV(std::array<std::array<std::shared_ptr<Tile>, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > resistanceMap, int startx, int starty, float force, float decay);
  std::vector<std::vector<float>> calculateFOV(std::array<std::array<std::shared_ptr<Tile>, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > resistanceMap, int startx, int starty, float radius);
  void castLight(int row, float start, float end, int xx, int xy, int yx, int yy);
  float radius(float dx, float dy);
  bool blockingCell(std::shared_ptr<Tile> tile);

private:
  int _startx;
  int _starty;
  float _radius;
  float _force;
  float _decay;
  std::array<std::array<std::shared_ptr<Tile>, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _resistanceMap;
  int _width;
  int _height;
  std::vector<std::vector<float> > _lightMap;

};
#endif
