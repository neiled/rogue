#include "actor.h"
#include "level.h"
#include "a_star.h"
#include "messages.h"
#include <deque>
#include "random.h"
#include "attribute_modifiers.h"
#include <SDL2/SDL.h>
#include "item.h"

Actor::Actor(int max_health, int xp_level) : _xp_level(xp_level)
{
  _attributes[Attribute::HEALTH] = max_health;
  _attributes[Attribute::CON] = max_health;
  _attributes[Attribute::ATK] = xp_level;//Random::BetweenNormal(1,_xp_level);
  _attributes[Attribute::DEF] = xp_level;//Random::BetweenNormal(1,_xp_level);
}

Actor::~Actor()
{
}

void Actor::setCurrentTile(Tile& newTile)
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
    this->setCurrentTile(*newTile);
    return true;
  }
}

bool Actor::explore()
{
  if(can_see_something_interesting())
  {
    Messages::Add("You see something and stop.");
    return false;
  }
  AStar searcher;
  _travelPath = searcher.explore(*_currentTile, _currentTile->level());
  if(_travelPath.empty())
  {
    _targetTile = nullptr;
    return false; //no where to explore
  }
  auto dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
  _travelPath.pop_front();
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
  return true;
}

bool Actor::can_see_something_interesting()
{
  auto visible_tiles = level().visible_tiles();
  for(auto tile : visible_tiles)
  {
    if(tile->actor() && tile->actor()->is_player() == false)
      return true;
  }

  return false;
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
      Messages::Add("You deal " + std::to_string(damage) + " damage");
    other->takeDamage(damage);
    if(other->dead())
    {
      if(is_player())
        Messages::Add("You killed them."); //TODO: Use the actors name
      killed(other);
    }
  }
  else if(is_player())
  {
    Messages::Add("You missed! chance of " + std::to_string(toHit));
  }
  else
  {
    Messages::Add("They missed!");
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
  SDL_Log("Attribute size: %d",_attributes.size());
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
