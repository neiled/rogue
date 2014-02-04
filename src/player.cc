#import "player.h"

Player::Player()
{
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
