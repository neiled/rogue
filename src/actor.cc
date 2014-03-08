#include "actor.h"
#include "level.h"
#include "a_star.h"
#include "messages.h"
#include <deque>
#include "random.h"
#include "attribute_modifiers.h"
#include <SDL2/SDL.h>
#include "item.h"

Actor::Actor(std::string name, int max_health, int xp_level) : Actor(name, max_health, xp_level, 5)
{
}

Actor::Actor(std::string name, int max_health, int xp_level, int inventory_size) : _xp_level(xp_level), _inventory(inventory_size), _name(name)
{
  _attributes[Attribute::HEALTH] = max_health;
  _attributes[Attribute::CON] = max_health;
  _attributes[Attribute::ATK] = xp_level;//Random::BetweenNormal(1,_xp_level);
  _attributes[Attribute::DEF] = xp_level;//Random::BetweenNormal(1,_xp_level);
}

Actor::~Actor()
{
}

void Actor::set_tile(Tile& newTile)
{
  if(_currentTile)
    _currentTile->removeActor();
  newTile.setActor(*this);
  _currentTile = &newTile;
  pickup_items();
}

void Actor::pickup_items()
{
}

Tile* Actor::tile() const
{
  return _currentTile;
}

Level& Actor::level()
{
  return _currentTile->level();
}

void Actor::moveLeft()
{
  direction = Actor::Direction::WEST;
  attemptMove(-1,0);
}

void Actor::moveRight()
{
  direction = Actor::Direction::EAST;
  attemptMove(1,0);
}
void Actor::moveUp()
{
  direction = Actor::Direction::NORTH;
  attemptMove(0,-1);
}
void Actor::moveDown()
{
  direction = Actor::Direction::SOUTH;
  attemptMove(0,1);
}

void Actor::move_to(Tile* tile)
{
  _targetTile = tile;
  push_command(Commands::CMD::CMD_MOVE_TO_TILE);
}

bool Actor::move_to_target()
{
  if(!_targetTile)
    return false;

  if(_targetTile == _currentTile)
  {
    _targetTile = nullptr;
    return false;
  }

  AStar searcher;
  _travelPath = searcher.plotPath(*_currentTile, *_targetTile);
  if(_travelPath.empty() == false)
  {
    Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
    _commandQueue.push_front(Commands::CMD::CMD_MOVE_TO_TILE);
    _commandQueue.push_front(dirCommand);
  }
  else
  {
    Messages::Add("No way to get to that location, too many obstacles!");
    _targetTile = nullptr;
    return false;
  }

  return true;

  
}

int Actor::x()
{
  return _currentTile->x();
}

int Actor::y()
{
  return _currentTile->y();
}

bool Actor::can_see_actor(Actor& actor)
{
  if(actor.tile()->is_lit() && this->tile()->is_lit())
    return true;


  return false;
}

bool Actor::attemptMove(int xModifier, int yModifier)
{
  int currentX = _currentTile->x();
  int currentY = _currentTile->y();

  int newX = currentX + xModifier;
  int newY = currentY + yModifier;
  
  auto newTile = checkCanMove(newX, newY);
  if(!newTile)
    return false;

  auto otherActor = newTile->actor();

  if(otherActor)
  {
    if((this->is_player() || otherActor->is_player()))
    {
      meleeAttack(otherActor);
      //if(otherActor->dead() == false)
        //otherActor->meleeAttack(this);
    }
    return false;
  }
  else
  {
    this->set_tile(*newTile);
    return true;
  }
}



void Actor::meleeAttack(Actor* other)
{
  if(!other || other->dead())
    return;

  float toHit = hit_chance(*other);

  if(Random::CheckChance(toHit))
  {
    int damage = calc_damage(*other);
    if(is_player())
      Messages::Add("You deal " + std::to_string(damage) + " damage to the " + other->name() +".");
    other->takeDamage(damage);
    if(other->dead())
    {
      if(is_player())
        Messages::Add("You killed the " + other->name() + ".");
      killed(other);
    }
  }
  else if(is_player())
  {
    Messages::Add("You missed the " + other->name() +"! chance of " + std::to_string(toHit));
  }
  else
  {
    Messages::Add("The " + name() + " missed!");
  }


  return;
}


int Actor::attack_score()
{
  //TODO make this a calc
  return atk();
}
int Actor::defense_score()
{
  //TODO make this a calc  
  return def();
}

int Actor::atk()
{
  return _attributes[Attribute::ATK];
}

int Actor::def()
{
  return _attributes[Attribute::DEF];
}

int Actor::calc_damage(Actor& other)
{
  int damage = 0;
  if(_weapon)
  {
    Messages::Add("Using your " + _weapon->name());
    damage =  _weapon->calc_damage(other);
  }
  else
  {
    damage = atk();
  }
  if(damage < 1)
    damage = 1;
  return Random::BetweenNormal(1,damage);
}

float Actor::hit_chance(Actor& other)
{
  float attackFloat = attack_score();
  float defenseFloat = other.defense_score();
  float floatChance = attackFloat / (attackFloat + defenseFloat);
  return static_cast<int>(floatChance * 100.0);
}

void Actor::takeDamage(int amount)
{
  if(is_player())
    Messages::Add("You take " + std::to_string(amount) + " damage");
  _attributes[Attribute::HEALTH] -= amount;
  if(_attributes[Attribute::HEALTH] <= 0)
  {
    _attributes[Attribute::HEALTH] = 0;
    die();
  }
}

bool Actor::dead() const
{
  return _attributes.at(Attribute::HEALTH) <= 0;
}

Tile* Actor::checkCanMove(int newX, int newY)
{
  if(newX < 0)
    return nullptr;
  if(newY < 0)
    return nullptr;
  if(newX >= Level::LEVEL_WIDTH)
    return nullptr;
  if(newY >= Level::LEVEL_HEIGHT)
    return nullptr;
  auto newTile = level().tile(newX, newY);
  if(newTile->tile_type() == Tile::TileType::Rock)
    return nullptr;
  return newTile;
}

void Actor::clearCommands()
{
  _commandQueue.clear();
}

Commands::CMD Actor::getCommandFromTiles(Tile& start, Tile& end)
{
  int xDiff = end.x() - start.x();
  int yDiff = end.y() - start.y();

  if(xDiff == -1)
    return Commands::CMD::CMD_MOVE_LEFT;
  if(xDiff == 1)
    return Commands::CMD::CMD_MOVE_RIGHT;
  if(yDiff == -1)
    return Commands::CMD::CMD_MOVE_UP;
  if(yDiff == 1)
    return Commands::CMD::CMD_MOVE_DOWN;
  return Commands::CMD::NOP;
}

void Actor::push_command(Commands::CMD command)
{
  _commandQueue.push_back(command);
}

Commands::CMD Actor::popCommand()
{
  Commands::CMD currentCommand = _commandQueue.front();
  _commandQueue.pop_front();
  return currentCommand;
}

bool Actor::hasCommands() const
{

  return _commandQueue.empty() == false;
}


int Actor::health()
{
  if(_attributes[Attribute::HEALTH] > _attributes[Attribute::CON])
    _attributes[Attribute::HEALTH] = _attributes[Attribute::CON];
  return _attributes[Attribute::HEALTH];
}

Inventory* Actor::inventory()
{
  return &_inventory;
}

void Actor::drop_items()
{
  for(auto item : _inventory.items())
  {
    _currentTile->add_item(item);
  }
  _inventory.empty();
}

void Actor::add_modifier(AttributeModifiers* modifier)
{
  if(modifier->turns() == 0)
    apply_modifier(modifier);
  else
    _modifiers.push_back(modifier);
}

void Actor::apply_modifier(AttributeModifiers* modifier)
{
  _attributes.at(modifier->attr()) += modifier->modifier();
}


int Actor::xp_level()
{
  return _xp_level;
}

Item* Actor::weapon()
{
  return _weapon;
}

void Actor::weapon(Item* weapon)
{
  _weapon = weapon;
}

std::string Actor::name()
{
  return _name;
}
