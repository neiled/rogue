#include "player.h"
#include "level.h"
#include "a_star.h"
#include "item.h"
#include "messages.h"
#include <deque>

Player::Player() : Actor(100, 1, 10), _xp(0)
{
  direction = Actor::Direction::EAST;
  _max_xp = calc_max_xp();
  _min_xp = calc_min_xp();
  _attributes[Attribute::ATK] = 5;
  _attributes[Attribute::DEF] = 5;
}

Player::~Player()
{
}


void Player::die() 
{
  Messages::Add("You died, do you want to try again? Y/N");
  //TODO: Message generation should be somewhere else...
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
    if(_inventory.full() == false)
    {
      if(item->item_type() != Item::ItemType::CORPSE)
      {
        _inventory.add(item);
      }
    }
    else
    {
      Messages.Add("You cannot carry any more items.");
      break;
    }
  }

  for(auto item : _inventory.items())
  {
    _currentTile->remove_item(item);
  }
}

void Player::killed(Actor* other)
{
  int xp_gained = 30;//TODO: calc xp for real
  increase_xp(xp_gained);
}

int32_t Player::calc_max_xp()
{
  return ((xp_level()*(xp_level()+1))*100)+(4000*(xp_level()/10.0));
}

int32_t Player::calc_min_xp()
{
  return ((xp_level()-1)*xp_level()*100)+(4000*((xp_level()-1)/10.0));
}
int32_t Player::xp()
{
  return _xp;
}

void Player::increase_xp(int amount)
{
  _xp += amount;
  while(_xp > calc_max_xp())
  {
    increase_level();
  }
}

void Player::increase_level()
{
  ++_xp_level;
  _max_xp = calc_max_xp();
  _min_xp = calc_min_xp();
  _attributes[Attribute::ATK]++;
  _attributes[Attribute::DEF]++;
  _attributes[Attribute::CON]+=10;
  _attributes[Attribute::HEALTH] = max_health();
}

int32_t Player::max_xp()
{
  return _max_xp;
}

int32_t Player::min_xp()
{
  return _min_xp;
}
