#ifndef PLAYER_H_
#define PLAYER_H_

class Level;
class Tile;

#include <deque>
#include "commands.h"
#include "world.h"




class Player
{
  public:
    Player();
    virtual ~Player();
    Level* getCurrentLevel();
    void setCurrentTile(Tile* currentTile);
    Tile* getCurrentTile();
    int getX();
    int getY();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void explore();
    World::Direction direction;

    void pushCommand(Commands::CMD command);
    Commands::CMD popCommand();
    bool hasCommands();
    
  private:
    Tile* _currentTile;
    Tile* _targetTile;

    deque<Commands::CMD> _commandQueue;
    deque<Tile*> _travelPath;
    
    bool attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
    Commands::CMD getCommandFromTiles(Tile* start, Tile* end);
};
#endif
