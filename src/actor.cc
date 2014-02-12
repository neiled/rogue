#include "actor.h"
#include "level.h"
#include "a_star.h"
#include <deque>

Actor::Actor()
{
}

Actor::~Actor()
{
}

void Actor::setCurrentTile(Tile* currentTile)
{
  _currentTile = currentTile;
}

Tile* Actor::getCurrentTile()
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
  
  Tile* newTile = checkCanMove(newX, newY);
  if(newTile != nullptr)
  {
    _currentTile = newTile;
    return true;
  }
  return false;
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
  Tile* newTile = getCurrentLevel()->getTile(newX, newY);
  if(newTile->getTileType() == Tile::TileType::Rock)
    return nullptr;
  return newTile;
}

void Actor::explore()
{
  if(_travelPath.empty())
  {
    //_targetTile = _currentTile->getLevel()->getTile(_currentTile->getX(), _currentTile->getY()-2);
    AStar searcher;
    //_travelPath = searcher.plotPath(_currentTile, _targetTile);
    _travelPath = searcher.explore(_currentTile, _currentTile->getLevel());
    if(_travelPath.empty())
    {
      _targetTile = nullptr;
      return; //no way to get to this square
    }
  }
  Commands::CMD dirCommand = getCommandFromTiles(_currentTile, _travelPath.front());
  _travelPath.pop_front();
  //if(_travelPath.empty() == false)
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
}

Commands::CMD Actor::getCommandFromTiles(Tile* start, Tile* end)
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

bool Actor::hasCommands()
{
  return _commandQueue.empty() == false;
}
