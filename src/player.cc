#include "player.h"
#include "level.h"
#include "a_star.h"
#include "item.h"
#include "messages.h"
#include <deque>

Player::Player() : Actor(100, 1)
{
  direction = Actor::Direction::EAST;
}

Player::~Player()
{
}


void Player::die() 
{
  Messages::Add("You died, do you want to try again? Y/N");
}

void Player::update()
{
}

int Player::max_health()
{
  return _attributes[Attribute::CON];
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


