#include "actor.h"
#include "level.h"
#include "a_star.h"
#include <deque>
#include "random.h"
#include <SDL2/SDL.h>

Actor::Actor()
{
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
}

Tile* Actor::getCurrentTile() const
{
  return _currentTile;
}

Level& Actor::level()
{
  return _currentTile->getLevel();
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
  int visibility = 5;//TODO get this number from somewhere...
  
  for(int y = this->y()-visibility; y < this->y() + visibility; ++y)
  {
    for(int x = this->x() - visibility; x < this->x() + visibility; ++x)
    {
      if(actor.x() == x && actor.y() == y)
        return true;
    }
  }
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

  auto otherActor = newTile->getActor();

  if(otherActor)
  {
    meleeAttack(otherActor);
    if(otherActor->dead() == false)
      otherActor->meleeAttack(this);
    return false;
  }
  else
  {
    this->setCurrentTile(*newTile);
    return true;
  }
}

void Actor::explore()
{
  if(_travelPath.empty())
  {
    AStar searcher;
    _travelPath = searcher.explore(*_currentTile, _currentTile->getLevel());
    if(_travelPath.empty())
    {
      _targetTile = nullptr;
      return; //no way to get to this square
    }
  }
  Commands::CMD dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
  _travelPath.pop_front();
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
}

void Actor::meleeAttack(Actor* other)
{
  if(!other)
    return;

  float toHit = getToHitChance(*other);

  if(Random::CheckChance(toHit))
  {
    int damage = Random::Between(0,10);
    other->takeDamage(damage);
  }

  SDL_Log("My health: %d", _health);
  SDL_Log("Their health: %d", other->_health);

  return;
}

int Actor::attack_score()
{
  //TODO make this a calc
  return 100;
}
int Actor::defense_score()
{
  //TODO make this a calc  
  return 100;
}

float Actor::getToHitChance(Actor& other)
{
  float attackFloat = attack_score();
  float defenseFloat = other.defense_score();
  float floatChance = attackFloat / (attackFloat + defenseFloat);
  return static_cast<int>(floatChance * 100.0);
}

void Actor::takeDamage(int amount)
{
  _health -= amount;
  if(_health <= 0)
    die();
}

bool Actor::dead() const
{
  return _health <= 0;
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
  auto newTile = level().getTile(newX, newY);
  if(newTile->getTileType() == Tile::TileType::Rock)
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

void Actor::pushCommand(Commands::CMD command)
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
