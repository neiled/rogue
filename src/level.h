#ifndef LEVEL_H_
#define LEVEL_H_

#include "tile.h"
#include <iostream>
#include <array>

class LevelBuilder;

using namespace std;


class Level
{
  const static int LEVEL_WIDTH = 100;
  const static int LEVEL_HEIGHT = 100;
  public:
    Level ();
    virtual ~Level ();
    void BuildLevel(LevelBuilder* builder);
    void SetType(int x, int y, Tile::TileType tileType);

  private:
    array<array<Tile*, LEVEL_WIDTH>, LEVEL_HEIGHT > _map;
};

#endif
