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
