#include "player.h"
#include "level.h"
#include "a_star.h"
#include <deque>

Player::Player()
{
  direction = World::Direction::EAST;
  _health = 100;
}

Player::~Player()
{
}

void Player::explore()
{
  if(_travelPath.empty())
  {
    AStar searcher;
    _travelPath = searcher.explore(_currentTile, _currentTile->getLevel());
    if(_travelPath.empty())
    {
      _targetTile = nullptr;
      return; //no way to get to this square
    }
  }
  Commands::CMD dirCommand = getCommandFromTiles(_currentTile, _travelPath.front());
  _travelPath.pop_front();
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
}

void Player::die()
{
  //TODO: End the game...
}
