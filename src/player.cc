#include "player.h"
#include "level.h"
#include "a_star.h"
#include "item.h"
#include "messages.h"
#include <deque>

Player::Player() : Actor("player", 100, 1, 10), _xp(0)
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
      Messages::Add("You cannot carry any more items.");
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

bool Player::explore()
{
  if(can_see_something_interesting())
  {
    Messages::Add("You see something and stop.");
    return false;
  }
  AStar searcher;
  _travelPath = searcher.explore(*_currentTile, _currentTile->level());
  if(_travelPath.empty())
  {
    _targetTile = nullptr;
    return false; //no where to explore
  }
  auto dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
  _travelPath.pop_front();
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
  return true;
}

void Player::set_tile(Tile& tile)
{
  Actor::set_tile(tile);
  add_seen_items();
}

bool Player::add_seen_items()
{
  bool seen = false;
  auto visible_tiles = _currentTile->level().visible_tiles();
  for(auto tile : visible_tiles)
  {
    for(auto item : tile->items())
    {
      if(item->interesting() == false)
        continue;
      if(find(_items_seen.begin(), _items_seen.end(), item) == _items_seen.end())
      {
        _items_seen.push_back(item);
        seen = true;
      }
    }
  }

  return seen;
}

bool Player::can_see_something_interesting()
{
  auto visible_tiles = level().visible_tiles();
  bool seen = false;
  for(auto tile : visible_tiles)
  {
    if(tile->actor() && tile->actor()->is_player() == false)
      return true;
    bool seen_items = add_seen_items();
    if(seen_items)
      seen = true;
  }

  return seen;
}
