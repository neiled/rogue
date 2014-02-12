#include "player.h"
#include "level.h"
#include "a_star.h"
#include <deque>

Player::Player()
{
  direction = World::Direction::EAST;
}

Player::~Player()
{
}

void Player::setCurrentTile(Tile* currentTile)
{
  _currentTile = currentTile;
}

Tile* Player::getCurrentTile()
{
  return _currentTile;
}

Level* Player::getCurrentLevel()
{
  return _currentTile->getLevel();
}

void Player::moveLeft()
{
  if(attemptMove(-1,0))
    direction = World::Direction::WEST;
}

void Player::moveRight()
{
  if(attemptMove(1,0))
    direction = World::Direction::EAST;
}
void Player::moveUp()
{
  if(attemptMove(0,-1))
    direction = World::Direction::NORTH;
}
void Player::moveDown()
{
  if(attemptMove(0,1))
    direction = World::Direction::SOUTH;
}

int Player::getX()
{
  return _currentTile->getX();
}

int Player::getY()
{
  return _currentTile->getY();
}

bool Player::attemptMove(int xModifier, int yModifier)
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

Tile* Player::checkCanMove(int newX, int newY)
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

void Player::explore()
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

Commands::CMD Player::getCommandFromTiles(Tile* start, Tile* end)
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

void Player::pushCommand(Commands::CMD command)
{
  _commandQueue.push_back(command);
}

Commands::CMD Player::popCommand()
{
  Commands::CMD currentCommand = _commandQueue.front();
  _commandQueue.pop_front();
  return currentCommand;
}

bool Player::hasCommands()
{
  return _commandQueue.empty() == false;
}
