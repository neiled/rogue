#include "player.h"
#include "level.h"
#include "a_star.h"
#include "item.h"
#include "messages.h"
#include <deque>
#include "item_factory.h"

Player::Player() : Actor("player", 1, 10), _xp(0)
{
  direction = Actor::Direction::EAST;
  _max_xp = calc_max_xp();
  _min_xp = calc_min_xp();
  _attributes[Attribute::ATK] = 2;
  _attributes[Attribute::DEF] = 1;
  _attributes[Attribute::CON] = 50;
  _attributes[Attribute::HEALTH] = max_health();
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
      if(item->can_pick_up())
      {
        _inventory.add(item);
        Messages::Add("You pick up the " + item->name());
      }
    }
    else
    {
      Messages::AddBad("You cannot carry any more items");
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
  Messages::PushGood("Your level increased to " + std::to_string(_xp_level)+"!");
}

int32_t Player::max_xp()
{
  return _max_xp;
}

int32_t Player::min_xp()
{
  return _min_xp;
}

int Player::max_damage(Actor& other)
{
  int damage = 0;
  if(_weapon)
  {
    Messages::Add("You attack with your " + _weapon->name());
    damage =  _weapon->calc_damage(other);
  }
  else
  {
    damage = atk();
  }
  if(damage < 1)
    damage = 1;

  return damage;
}

bool Player::explore()
{
  if(can_see_something_interesting(false))
  {
    return false;
  }
  if(_travelPath.empty())
  {
    AStar searcher;
    _travelPath = searcher.explore(*_currentTile, _currentTile->level());
  }
  if(_travelPath.empty())
  {
    _targetTile = nullptr;
    return false; //no where to explore
  }
  auto dirCommand = getCommandFromTiles(*_currentTile, *_travelPath.front());
  _travelPath.pop_front();
  _commandQueue.push_front(Commands::CMD::CMD_EXPLORE);
  _commandQueue.push_front(dirCommand);
  return false; //don't spend a turn on actual explore command, just on movement
}

void Player::set_tile(Tile& tile)
{
  Actor::set_tile(tile);
}

void Player::add_seen_items()
{
  auto visible_tiles = _currentTile->level().visible_tiles();
  for(auto tile : visible_tiles)
  {
    if(tile->interesting())
    {
      if(find(_interesting_tiles_seen.begin(), _interesting_tiles_seen.end(), tile)
          == _interesting_tiles_seen.end())
      {
        _interesting_tiles_seen.push_back(tile);
      }
    }
    for(auto item : tile->items())
    {
      if(item->interesting())
      {
        if(find(_interesting_items_seen.begin(), _interesting_items_seen.end(), item)
            == _interesting_items_seen.end())
        {
          _interesting_items_seen.push_back(item);
        }
      }
    }
  }



}

bool Player::can_see_something_interesting(bool quiet)
{
  bool seen = false;

  if(can_see_monster(quiet))
    seen = true;
  if(can_see_unknown_item(quiet))
  {
    seen = true;
  }
  if(can_see_interesting_tile(quiet))
  {
    seen = true;
  }
  if(seen && quiet == false)
    Messages::Push();
  add_seen_items();
  return seen;
}

bool Player::can_see_monster(bool quiet)
{
  bool seen = false;
  auto visible_tiles = level().visible_tiles();
  for(auto tile : visible_tiles)
  {
    if(tile->actor() && tile->actor()->is_player() == false)
    {
      if(!quiet)
        Messages::Add("You see a " + tile->actor()->name());
      seen = true;
    }
  }
  return seen;
}

bool Player::can_see_interesting_tile(bool quiet)
{
  bool seen = false;
  auto visible_tiles = _currentTile->level().visible_tiles();
  for(auto tile : visible_tiles)
  {
      if(tile->interesting() == false)
        continue;
      if(find(_interesting_tiles_seen.begin(), _interesting_tiles_seen.end(), tile)
          == _interesting_tiles_seen.end())
      {
        if(!quiet)
          Messages::Add("You see " + tile->name());
        seen = true;
      }
  }
  return seen;
}
bool Player::can_see_unknown_item(bool quiet)
{
  bool seen = false;
  auto visible_tiles = _currentTile->level().visible_tiles();
  for(auto tile : visible_tiles)
  {
    for(auto item : tile->items())
    {
      if(item->interesting() == false)
        continue;
      if(find(_interesting_items_seen.begin(), _interesting_items_seen.end(), item)
          == _interesting_items_seen.end())
      {
        if(!quiet)
          Messages::Push("You see a " + item->name());
        seen = true;
      }
    }
  }
  return seen;
}
