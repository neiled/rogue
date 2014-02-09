#ifndef SHADOW_H
#define SHADOW_H 

#include <array>
#include <vector>
#include "level.h"

using namespace std;

class Tile;

class ShadowCasting
{
public:
  ShadowCasting ();
  virtual ~ShadowCasting ();
  vector<vector<float>> calculateFOV(array<array<Tile*, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > resistanceMap, int startx, int starty, float force, float decay);
  vector<vector<float>> calculateFOV(array<array<Tile*, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > resistanceMap, int startx, int starty, float radius);
  void castLight(int row, float start, float end, int xx, int xy, int yx, int yy);
  float radius(float dx, float dy);
  bool blockingCell(Tile* tile);

private:
  int _startx;
  int _starty;
  float _radius;
  float _force;
  float _decay;
  array<array<Tile*, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _resistanceMap;
  int _width;
  int _height;
  vector<vector<float> > _lightMap;

};
#endif
