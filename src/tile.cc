#include <SDL2/SDL.h>
#include <cmath>
#include "tile.h"
#include "actor.h"
#include "item.h"
#include "level.h"

Tile::Tile(TileType tileType, Level& level, int x, int y) :_level(level)
{
  _tileType = tileType;
  _x = x;
  _y = y;
}

Tile::~Tile()
{
  for(auto item : _items)
  {
    if(item)
    {
      delete item;
    }
  }
}

void Tile::setActor(Actor& actor)
{
  _actor = &actor;
}

void Tile::removeActor()
{
  _actor= nullptr;
}

Actor* Tile::actor()
{
  return _actor;
}

void Tile::setTileType(TileType tileType)
{
  _tileType = tileType;
}

TileType Tile::tile_type()
{
  return _tileType;
}

Level& Tile::level()
{
  return _level;
}

std::vector<Item*> Tile::items()
{
  return _items;
}

void Tile::add_item(Item * item)
{
  _items.push_back(item);
}

void Tile::remove_item(Item* item)
{
  _items.erase(remove(_items.begin(), _items.end(), item), _items.end());
}

int Tile::x() const
{
  return _x;
}


int Tile::y() const
{
  return _y;
}

bool Tile::is_lit() const
{
  return _level.light_map(_x, _y) == Level::LightType::Lit;
}

double Tile::distanceTo(const Tile& otherTile)
{
  return sqrt((otherTile.x() - _x)*(otherTile.x() - _x) + (otherTile.y() - _y) * (otherTile.y() - _y));
}

bool Tile::interesting()
{
  if(_tileType == TileType::StairsDown)
    return true;
  if(_tileType == TileType::StairsUp)
    return true;
  return false;
}

std::string Tile::name()
{
  switch(_tileType)
  {
    case TileType::StairsDown:
      return "Stairs Down";
    case TileType::StairsUp:
      return "Stairs Up";
    case TileType::Rock:
      return "Rock";
    case TileType::Floor:
      return "Floor";
    case TileType::Door:
      return "Door";
  }
}

