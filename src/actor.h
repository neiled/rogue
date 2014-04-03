#ifndef ACTOR_H_
#define ACTOR_H_


#include <deque>
#include <map>
#include <string>
#include <cstdint>
#include "commands.h"
#include "inventory.h"
#include "game_object.h"

class Tile;
class Level;
class AttributeModifiers;
class Weapon;
class Chest;

class Actor : public GameObject
{
  public:
    Actor(std::string name, int xp_level);
    Actor(std::string name, int xp_level, int inventory_size, float speed);
    virtual ~Actor();

    enum class Direction {EAST=0, WEST=1, NORTH=2, SOUTH=3};
    enum class Attribute {ATK=0, DEF, HEALTH, CON, DMG};
    
    Direction direction;
    
    Level& level();
    virtual void set_tile(Tile& currentTile);
    Tile* tile() const;

    Inventory* inventory();
    Chest* chest();
    
    int x();
    int y();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void move_to(Tile* tile);
    bool move_to_target();
    
    virtual void start_turn();
    virtual void end_turn();


    bool can_see_actor(Actor& actor);
    virtual bool can_see_something_interesting(bool quiet = true);
    virtual bool can_see_monster(bool quiet = true);
    

    void push_command(Commands::CMD command);
    void push_command(Commands::CMD command, GameObject* target);
    void push_command(Commands::CMD command, GameObject* target, int cost);
    Command popCommand();
    Command next_command();
    bool hasCommands() const;
    bool can_afford_next_command();
    int action_points();
    void use_action_points(int amount);
    void clearCommands();

    void takeDamage(int amount, Actor* other);
    int calc_damage(Actor& other);
    virtual int max_damage(Actor& other) = 0;
    virtual int min_damage(Actor& other) = 0;

    bool dead() const;
    
    
    virtual int max_health() = 0;
    int health();
    int previous_health();
    

    void drop_items();

    void add_modifier(AttributeModifiers modifier);
    
    int xp_level();

    virtual bool is_player() = 0;
    
    int atk();
    int def();
    int dmg();
    int con();

    Item* weapon();
    void weapon(Item* weapon);
    
    
    Actor* target_actor();
    void target_actor(Actor* actor);
    
  protected:
    Tile* _currentTile = nullptr;
    Tile* _targetTile = nullptr;
    //int _health;

    std::deque<Command> _commandQueue;
    std::deque<Tile*> _travelPath;
    Command getCommandFromTiles(Tile& start, Tile& end);

    std::vector<AttributeModifiers> _modifiers;

    std::map<Actor::Attribute, int> _attributes;

    Inventory _inventory;
    
    bool attemptMove(int newX, int newY);
    Tile* checkCanMove(int newX, int newY);
    void meleeAttack(Actor* other);
    float hit_chance(Actor& other);
    int calc_min_damage(Actor&);
    int calc_max_damage(Actor&);


    virtual void die() = 0;
    virtual void killed(Actor* other) = 0;

    void apply_modifier(AttributeModifiers modifier);
    int calc_modified(Actor::Attribute attr);

    virtual void pickup_items();

    int _xp_level;
    
    int _previous_health;

    Item* _weapon = nullptr;
    
    Actor* _target_actor = nullptr;

    int _action_points;

    float _speed;



};
#endif
