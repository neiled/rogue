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

Level* Player::getCurrentLevel()
{
  return _currentTile->getLevel();
}
