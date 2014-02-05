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
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    
  private:
    Tile* _currentTile;
    void attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
};
#endif
