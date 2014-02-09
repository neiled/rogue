#include "player.h"
#include "level.h"

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
