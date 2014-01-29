#ifndef PLAYER_H_
#define PLAYER_H_

class Tile;


class Player
{
  public:
    Player();
    virtual ~Player();

  private:
    Tile* _currentTile;
};
#endif
