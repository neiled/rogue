#ifndef ACTOR_H_
#define ACTOR_H_

class Level;
class Tile;

#include <deque>
#include "commands.h"
#include "world.h"

class Actor
{
  public:
    Actor();
    virtual ~Actor();
    Level* getCurrentLevel();
    void setCurrentTile(Tile* currentTile);
    Tile* getCurrentTile();
    int getX();
    int getY();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    World::Direction direction;

    void pushCommand(Commands::CMD command);
    Commands::CMD popCommand();
    bool hasCommands();
    
  protected:
    Tile* _currentTile = nullptr;
    Tile* _targetTile = nullptr;

    std::deque<Commands::CMD> _commandQueue;
    std::deque<Tile*> _travelPath;
    
    bool attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
    Commands::CMD getCommandFromTiles(Tile* start, Tile* end);
    bool attack(Actor* other);
};
#endif