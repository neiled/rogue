#include "player.h"
#include "level.h"
#include "a_star.h"
#include <deque>

Player::Player() : Actor(max_health())
{
  direction = Actor::Direction::EAST;
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

int Player::max_health()
{
  return 100;
}


