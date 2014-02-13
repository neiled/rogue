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

void Actor::setCurrentTile(std::shared_ptr<Tile> newTile)
{
  if(_currentTile)
    _currentTile->removeActor();
  newTile->setActor(this);
  _currentTile = newTile;
}

std::shared_ptr<Tile> Actor::getCurrentTile()
{
  return _currentTile;
}

Level* Actor::getCurrentLevel()
{
  return _currentTile->getLevel();
}

void Actor::moveLeft()
{
  if(attemptMove(-1,0))
    direction = World::Direction::WEST;
}

void Actor::moveRight()
{
  if(attemptMove(1,0))
    direction = World::Direction::EAST;
}
void Actor::moveUp()
{
  if(attemptMove(0,-1))
    direction = World::Direction::NORTH;
}
void Actor::moveDown()
{
  if(attemptMove(0,1))
    direction = World::Direction::SOUTH;
}

int Actor::x()
{
  return _currentTile->getX();
}

int Actor::y()
{
  return _currentTile->getY();
}

bool Actor::can_see_actor(Actor& actor)
{
  int visibility = 5;//TODO get this number from somewhere...
  
  for(int y = y()-visibility; y < y() + visibility; ++y)
  {
    for(int x = x() - visibility; x < x() + visibility; ++x)
    {
      if(actor.x() == x && actor.y == y)
        return true;
    }
  }
  return false;
}

bool Actor::attemptMove(int xModifier, int yModifier)
{
  int currentX = _currentTile->getX();
  int currentY = _currentTile->getY();

  int newX = currentX + xModifier;
  int newY = currentY + yModifier;
  
  auto newTile = checkCanMove(newX, newY);
  if(!newTile)
    return false;

  if(meleeAttack(newTile->getActor()))
  {
    this->setCurrentTile(newTile);
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

  float toHit = getToHitChance();

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
int defense_score()
{
  //TODO make this a calc  
  return 100;
}

float Actor::getToHitChance(Actor& other)
{
  return static_cast<float>(attack_score()) / (attack_score() + other.defense_score());
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

std::shared_ptr<Tile> Actor::checkCanMove(int newX, int newY)
{
  if(newX < 0)
    return nullptr;
  if(newY < 0)
    return nullptr;
  if(newX >= Level::LEVEL_WIDTH)
    return nullptr;
  if(newY >= Level::LEVEL_HEIGHT)
    return nullptr;
  auto newTile = getCurrentLevel()->getTile(newX, newY);
  if(newTile->getTileType() == Tile::TileType::Rock)
    return nullptr;
  return newTile;
}

void Actor::clearCommands()
{
  _commandQueue.clear();
}

Commands::CMD Actor::getCommandFromTiles(std::shared_ptr<Tile> start, std::shared_ptr<Tile> end)
{
  int xDiff = end->getX() - start->getX();
  int yDiff = end->getY() - start->getY();

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
