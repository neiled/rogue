#ifndef PLAYER_H_
#define PLAYER_H_

class Level;

#include "tile.h"


class Player
{
  public:
    Player();
    virtual ~Player();
    Level* getCurrentLevel();
    void setCurrentTile(Tile* currentTile);
    Tile* getCurrentTile();
    
  private:
    Tile* _currentTile;
};
#endif
