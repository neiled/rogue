#import "player.h"

Player::Player()
{
}

Player::~Player()
{
}

Level* Player::getCurrentLevel()
{
  return _currentTile->getLevel();
}
