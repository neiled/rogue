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

Tile* Actor::getCurrentTile()
{
  return _currentTile;
}

Level& Actor::level()
{
  return _currentTile->getLevel();
}

void Actor::moveLeft()
{
  if(attemptMove(-1,0))
    direction = Actor::Direction::WEST;
}

void Actor::moveRight()
{
  if(attemptMove(1,0))
    direction = Actor::Direction::EAST;
}
void Actor::moveUp()
{
  if(attemptMove(0,-1))
    direction = Actor::Direction::NORTH;
}
void Actor::moveDown()
{
  if(attemptMove(0,1))
    direction = Actor::Direction::SOUTH;
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

  if(meleeAttack(newTile->getActor()))
  {
    this->setCurrentTile(*newTile);
    return true;
  }
  else
    newTile->getActor()->meleeAttack(this);

  return false;
}

bool Actor::meleeAttack(Actor* other)
{
  if(!other)
    return true;

  float toHit = getToHitChance(*other);
  SDL_Log("Hit chance %f", toHit);

  auto otherTile = other->getCurrentTile();

  if(Random::CheckChance(toHit))
  {
    int damage = Random::Between(0,10);
    other->takeDamage(damage);
  }

  return false;
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
  int floatChance = static_cast<float>(attack_score()) / (attack_score() + other.defense_score());
  return floatChance * 100;
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
