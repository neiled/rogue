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
    void setCurrentTile(std::shared_ptr<Tile> currentTile);
    std::shared_ptr<Tile> getCurrentTile();
    int getX();
    int getY();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    World::Direction direction;

    void pushCommand(Commands::CMD command);
    Commands::CMD popCommand();
    bool hasCommands() const;
    void clearCommands();

    void takeDamage(int amount);

    bool dead() const;
    
  protected:
    std::shared_ptr<Tile> _currentTile;
    std::shared_ptr<Tile> _targetTile = nullptr;
    int _health;

    std::deque<Commands::CMD> _commandQueue;
    std::deque<std::shared_ptr<Tile>> _travelPath;
    Commands::CMD getCommandFromTiles(std::shared_ptr<Tile> start, std::shared_ptr<Tile> end);
    
    bool attemptMove(int newX, int newY);
    std::shared_ptr<Tile> checkCanMove(int newX, int newY);
    bool meleeAttack(Actor* other);
    float getToHitChance(/*Item* item*/);
    virtual void die() = 0;


};
#endif
