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
  SDL_Log("setting new tile to %d,%d", newTile->getX(), newTile->getY());
  if(_currentTile)
    _currentTile->removeActor();
  newTile->setActor(this);
  _currentTile = newTile;
  SDL_Log("new tile set to %d,%d", getCurrentTile()->getX(), getCurrentTile()->getY());
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

int Actor::getX()
{
  if(!_currentTile)
    SDL_Log("Nothing in x");
  return _currentTile->getX();
}

int Actor::getY()
{
  return _currentTile->getY();
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

  SDL_Log("Getting other tile...");
  if(!other)
    SDL_Log("Other has gone...");
  auto otherTile = other->getCurrentTile();
  SDL_Log("Done getting other tile...");
  SDL_Log("Attacking monster at %d,%d", otherTile->getX(), otherTile->getY());
  if(otherTile->getActor() != other)
    SDL_Log("Tile doesn't think the monster is on it...");

  if(Random::CheckChance(toHit))
  {
    int damage = Random::Between(0,10);
    other->takeDamage(damage);
  }

  return false;
}

float Actor::getToHitChance()
{
  //TODO: This would be based on the weapon used probably?
  //For now we'll just call it 100%...
  //
  return 100.0f;
}

void Actor::takeDamage(int amount)
{
  SDL_Log("Taking damage");
  _health -= amount;
  SDL_Log("I now have %d remaining health", _health);
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
