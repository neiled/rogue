#include "player.h"
#include "level.h"
#include "a_star.h"
#include "item.h"
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

void Player::pickup_items()
{
  for(auto item : _currentTile->items())
  {
    if(item->item_type() != Item::ItemType::CORPSE)
      _inventory.add(item);
  }

  for(auto item : _inventory.items())
  {
    _currentTile->remove_item(item);
  }
}


