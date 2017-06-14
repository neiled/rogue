#include "actor.h"
#include "level.h"
#include "a_star.h"
#include "messages.h"
#include "attribute_modifiers.h"
#include "item.h"
#include "chest.h"
#include "wand.h"

Actor::Actor(std::string name, int xp_level) : Actor(name, xp_level, 5, 1)
{
}

Actor::Actor(std::string name, int xp_level, int inventory_size, float speed) : GameObject(name), _xp_level(xp_level), _inventory(inventory_size), _action_points(0), _speed(speed)
{
  _attributes[Attribute::ATK] = xp_level+5;//Random::BetweenNormal(1,_xp_level);
  _attributes[Attribute::DEF] = xp_level+5;//Random::BetweenNormal(1,_xp_level);
  _attributes[Attribute::DMG] = 0;
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

void Actor::start_turn()
{
  _previous_health = health();
  if(_action_points < 0)
    _action_points = 0;
  _action_points += 100;
}

void Actor::end_turn()
{
  if(_attributes[Attribute::HEALTH] > _attributes[Attribute::CON])
    _attributes[Attribute::HEALTH] = _attributes[Attribute::CON];

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

bool Actor::can_see_something_interesting(bool quiet)
{
  return false;
}

bool Actor::can_see_monster(bool quiet)
{
  return false;
}


bool Actor::move_to_target()
{
  if(!_targetTile)
    return false;

  if(_targetTile == _currentTile)
  {
    _targetTile = nullptr;
    _travelPath.clear();
    return false;
  }

  if(can_see_monster())
  {
    _targetTile = nullptr;
    _travelPath.clear();
    return false;
  }

  if(_travelPath.empty())
  {
    AStar searcher;
    _travelPath = searcher.plotPath(*_currentTile, *_targetTile);
    Messages::Push("Moving to tile.");
  }

  if(_travelPath.empty() == false)
  {
    auto dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
    _travelPath.pop_front();
    _commandQueue.push_front(Command{Commands::CMD::CMD_MOVE_TO_TILE});
    _commandQueue.push_front(dirCommand);
  }
  else
  {
    Messages::Add("No way to get to that location, too many obstacles");
    _targetTile = nullptr;
    _travelPath.clear();
    return false;
  }

  return false;//Don't spend a turn setting up, turns spent on actual movement


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

  _target_actor = other;

  float toHit = hit_chance(*other);

  if(Random::CheckChance(toHit))
  {
    int damage = calc_damage(*other);
    if(is_player())
      Messages::AddGood("You deal " + std::to_string(damage) + " damage to the " + other->name());
    other->takeDamage(damage, this);
    if(other->dead())
    {
      if(is_player())
        Messages::AddGood("You killed the " + other->name());
      killed(other);
    }
  }
  else if(is_player())
  {
    Messages::AddBad("You missed the " + other->name() +"! chance of " + std::to_string(static_cast<int>(toHit)));
  }
  else
  {
    Messages::Add("The " + name() + " missed");
  }

  _action_points -= 100; //TODO: should use some form of attack speed here?


  return;
}

void Actor::rangedAttack(Tile* tile)
{
  ranged_weapon()->fire(*this, *tile);

  _action_points -= 100;

}

Chest* Actor::chest()
{
  for(auto current_item : tile()->items())
  {
    if(current_item->item_type() == ItemType::CHEST)
      return static_cast<Chest*>(current_item);
  }

  return nullptr;

}



int Actor::atk()
{
  return calc_modified(Attribute::ATK);
}

int Actor::def()
{
  return calc_modified(Attribute::DEF);
}

int Actor::dmg()
{
  return calc_modified(Attribute::DMG);
}


int Actor::calc_damage(Actor& other)
{
  int max_damage = this->max_damage(other);
  int min_damage = this->min_damage(other);

  auto base_damage = Random::BetweenNormal(min_damage, max_damage);
  auto total_damage = base_damage;
  total_damage += dmg();

  return total_damage;
}

float Actor::hit_chance(Actor& other)
{
  float attackFloat = static_cast<float>(atk())*1.5;
  float defenseFloat = other.def();
  float floatChance = attackFloat / (atk() + defenseFloat);
  return static_cast<int>(floatChance * 100.0);
}

void Actor::takeDamage(int amount, Actor* other)
{
  if(is_player())
  {
    auto message = "You take " + std::to_string(amount) + " damage";
    if(other)
      message = message + " from the " + other->name();
    Messages::AddBad(message);
  }
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
  if(newTile->tile_type() == TileType::Rock)
    return nullptr;
  return newTile;
}

void Actor::clearCommands()
{
  _commandQueue.clear();
}

Command Actor::getCommandFromTiles(Tile& start, Tile& end)
{
  int xDiff = end.x() - start.x();
  int yDiff = end.y() - start.y();
  Commands::CMD dir;

  if(xDiff == -1)
    dir = Commands::CMD::CMD_MOVE_LEFT;
  else if(xDiff == 1)
    dir = Commands::CMD::CMD_MOVE_RIGHT;
  else if(yDiff == -1)
    dir = Commands::CMD::CMD_MOVE_UP;
  else if(yDiff == 1)
    dir = Commands::CMD::CMD_MOVE_DOWN;
  else
    dir = Commands::CMD::NOP;

  return Command(dir, nullptr, 100/_speed);
}

//TODO: Should be called add_command
void Actor::push_command(Commands::CMD command)
{
  _commandQueue.push_back(Command{command});
}

void Actor::push_command(Commands::CMD command, GameObject* target)
{
  _commandQueue.push_back(Command{command, target});
}

void Actor::push_command(Commands::CMD command, int cost)
{
  _commandQueue.push_back(Command{command, nullptr, cost});
}

void Actor::push_command(Commands::CMD command, GameObject* target, int cost)
{
  _commandQueue.push_back(Command{command, target, cost});
}

Command Actor::popCommand()
{
  Command currentCommand = _commandQueue.front();
  _commandQueue.pop_front();
  return currentCommand;
}

Command Actor::next_command()
{
  return _commandQueue.front();
}

bool Actor::hasCommands() const
{

  return _commandQueue.empty() == false;
}

bool Actor::can_afford_next_command()
{
  if(_commandQueue.empty())
    return false;
  return _commandQueue.front().cost <= _action_points;
}

int Actor::action_points()
{
  return _action_points;
}

void Actor::use_action_points(int amount)
{
  _action_points -= amount;
}



int Actor::health()
{
  return _attributes[Attribute::HEALTH];
}

int Actor::previous_health()
{
  return _previous_health;
}

Inventory* Actor::inventory()
{
  return &_inventory;
}

void Actor::drop_items()
{
  for(auto item : _inventory.items())
  {
    if(is_player() == false)
      Messages::Add("The " + name() + " dropped " + item->name());
    _currentTile->add_item(item);
  }
  _inventory.clear();
}

void Actor::add_modifier(AttributeModifiers modifier)
{
  if(modifier.turns() == 0)
    apply_modifier(modifier);
  else
    _modifiers.push_back(modifier);
}

void Actor::apply_modifier(AttributeModifiers modifier)
{
  _attributes.at(modifier.attr()) += modifier.modifier();
}


int Actor::calc_modified(Actor::Attribute attr)
{
  int base = _attributes[attr];
  for(auto current_attr_mod : _modifiers)
  {
    if(current_attr_mod.attr() == attr)
      base += current_attr_mod.modifier();
  }

  if(_weapon)
  {
    for(auto current_attr_mod : _weapon->modifiers())
    {
      if(current_attr_mod.attr() == attr)
        base += current_attr_mod.modifier();
    }
  }

  return base;
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

RangedWeapon* Actor::ranged_weapon()
{
  return _ranged_weapon;
}

void Actor::ranged_weapon(RangedWeapon* weapon)
{
  _ranged_weapon = weapon;
}

Actor* Actor::target_actor()
{
  return _target_actor;
}

void Actor::target_actor(Actor* actor)
{
  _target_actor = actor;
}
