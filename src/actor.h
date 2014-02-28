#ifndef ACTOR_H_
#define ACTOR_H_


#include <deque>
#include <map>
#include <cstdint>
#include "commands.h"
#include "inventory.h"

class Tile;
class Level;
class AttributeModifiers;

class Actor
{
  public:
    Actor(int max_health, int xp_level);
    virtual ~Actor();

    enum class Direction {EAST=0, WEST=1, NORTH=2, SOUTH=3};
    enum class Attribute {ATK, DEF, HEALTH, CON};
    
    Direction direction;
    
    virtual void update() = 0;
    
    Level& level();
    void setCurrentTile(Tile& currentTile);
    Tile* tile() const;

    Inventory* inventory();
    
    int x();
    int y();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    bool explore();
    
    bool can_see_actor(Actor& actor);
    

    void pushCommand(Commands::CMD command);
    Commands::CMD popCommand();
    bool hasCommands() const;
    void clearCommands();

    void takeDamage(int amount);

    bool dead() const;
    
    int attack_score();
    int defense_score();
    
    virtual int max_health() = 0;
    int health();
    
    bool can_see_something_interesting();

    void drop_items();

    void add_modifier(AttributeModifiers* modifier);
    
    int32_t xp();
    int32_t max_xp();
    int xp_level();

    
  protected:
    Tile* _currentTile = nullptr;
    Tile* _targetTile = nullptr;
    //int _health;

    std::deque<Commands::CMD> _commandQueue;
    std::deque<Tile*> _travelPath;
    Commands::CMD getCommandFromTiles(Tile& start, Tile& end);

    std::vector<AttributeModifiers*> _modifiers;

    std::map<Actor::Attribute, int> _attributes;

    Inventory _inventory;
    
    bool attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
    void meleeAttack(Actor* other);
    float hit_chance(Actor& other);
    int calc_damage(Actor&);

    int atk();

    virtual void die() = 0;
    virtual bool is_player() = 0;

    void apply_modifier(AttributeModifiers* modifier);
    virtual void pickup_items();
    
    int32_t _xp;
    int32_t _max_xp;
    int32_t calc_max_xp();
    int _xp_level;

    Item* _weapon;



};
#endif
