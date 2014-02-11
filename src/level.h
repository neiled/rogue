#ifndef LEVEL_H_
#define LEVEL_H_

#include <iostream>
#include <array>
#include "tile.h"


class LevelBuilder;
class Player;
class Level;

using namespace std;


class Level
{
  public:
    Level (int depth);
    virtual ~Level ();

    enum class LightType {Unseen, Unlit, Lit};

    void update(Player* player);
    void updateGraphics();
    Level::LightType getTileLightMap(int x, int y);
    void setType(int x, int y, Tile::TileType tileType);
    Tile* getTile(int x, int y);
    int getDepth();
    Tile* getTileOfType(Tile::TileType typeToLookFor);
    

    const static int LEVEL_WIDTH = 100;
    const static int LEVEL_HEIGHT = 100;

  private:
   int _depth; 
    
    void updateLightMap(Player* player);
    void resetLightMap();
    
    array<array<Tile*, LEVEL_WIDTH>, LEVEL_HEIGHT > _map;
    array<array<Level::LightType, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _light_map;
  
};

#endif
