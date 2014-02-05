#ifndef LEVEL_H_
#define LEVEL_H_

#include "tile.h"
#include <iostream>
#include <array>

class LevelBuilder;

using namespace std;


class Level
{
  public:
    Level ();
    virtual ~Level ();
    void update(Player* player);
    bool getTileLightMap(int x, int y)
    void setType(int x, int y, Tile::TileType tileType);
    Tile* getTile(int x, int y);
    
    enum class LightType {Unseen, Unlit, Lit};

    const static int LEVEL_WIDTH = 100;
    const static int LEVEL_HEIGHT = 100;

  private:
    
    
    void updateLightMap(Player* player)
    
    array<array<Tile*, LEVEL_WIDTH>, LEVEL_HEIGHT > _map;
    array<array<Level::LightType, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _light_map;
  
};

#endif
