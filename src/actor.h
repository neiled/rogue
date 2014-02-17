#ifndef ACTOR_H_
#define ACTOR_H_


#include <deque>
#include "commands.h"

class Tile;
class Level;

class Actor
{
  public:
    Actor();
    virtual ~Actor();

    enum class Direction {EAST=0, WEST=1, NORTH=2, SOUTH=3};
    
    Direction direction;
    
    virtual void update() = 0;
    
    Level& level();
    void setCurrentTile(Tile& currentTile);
    Tile* tile() const;
    
    int x();
    int y();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void explore();
    
    bool can_see_actor(Actor& actor);
    

    void pushCommand(Commands::CMD command);
    Commands::CMD popCommand();
    bool hasCommands() const;
    void clearCommands();

    void takeDamage(int amount);

    bool dead() const;
    
    int attack_score();
    int defense_score();
    
  protected:
    Tile* _currentTile = nullptr;
    Tile* _targetTile = nullptr;
    int _health;

    std::deque<Commands::CMD> _commandQueue;
    std::deque<Tile*> _travelPath;
    Commands::CMD getCommandFromTiles(Tile& start, Tile& end);
    
    bool attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
    void meleeAttack(Actor* other);
    float getToHitChance(Actor& other);
    virtual void die() = 0;


};
#endif
