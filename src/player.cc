#include "player.h"
#include "level.h"

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

void Player::moveLeft()
{
  attemptMove(-1,0);
}

void Player::moveRight()
{
  attemptMove(1,0);
}
void Player::moveUp()
{
  attemptMove(0,-1);
}
void Player::moveDown()
{
  attemptMove(0,1);
}

void Player::attemptMove(int xModifier, int yModifier)
{
  int currentX = _currentTile->getX();
  int currentY = _currentTile->getY();

  int newX = currentX + xModifier;
  int newY = currentY + yModifier;
  
  Tile* newTile = checkCanMove(newX, newY);
  if(newTile != NULL)
  {
    _currentTile = newTile;
  }
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
  if(newTile->getTileType() != Tile::TileType::Floor)
    return newTile;//nullptr;
  return newTile;
}
