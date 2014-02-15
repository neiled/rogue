#include "player.h"
#include "level.h"
#include "a_star.h"
#include <deque>

Player::Player()
{
  direction = Actor::Direction::EAST;
  _health = 100;
}

Player::~Player()
{
}


void Player::die() 
{
  //TODO: End the game...
}

void Player::update()
{
}


