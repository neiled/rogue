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
  int currentX = getCurrentTile()->getX();
  int currentY = getCurrentTile()->getY();

  int newX = currentX - 1;
  int newY = currentY;

  attemptMove(newX, newY);
}

void Player::moveRight()
{
  int currentX = getCurrentTile()->getX();
  int currentY = getCurrentTile()->getY();

  int newX = currentX + 1;
  int newY = currentY;

  attemptMove(newX, newY);
}
void Player::moveUp()
{
  int currentX = getCurrentTile()->getX();
  int currentY = getCurrentTile()->getY();

  int newX = currentX;
  int newY = currentY - 1;

  attemptMove(newX, newY);
}
void Player::moveDown()
{
  int currentX = getCurrentTile()->getX();
  int currentY = getCurrentTile()->getY();

  int newX = currentX;
  int newY = currentY + 1;

  attemptMove(newX, newY);
}

void Player::attemptMove(int newX, int newY)
{
  Tile* newTile = checkCanMove(newX, newY);
  if(newTile != NULL)
  {
    _currentTile = newTile;
  }
}

Tile* Player::checkCanMove(int newX, int newY)
{
  if(newX < 0)
    return NULL;
  if(newY < 0)
    return NULL;
  if(newX >= Level::LEVEL_WIDTH)
    return NULL;
  if(newY >= Level::LEVEL_HEIGHT)
    return NULL;
  Tile* newTile = getCurrentLevel()->getTile(newX, newY);
  if(newTile->getTileType() != Tile::TileType::Floor)
    return NULL;
  return newTile;
}
