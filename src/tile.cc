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

Tile::TileType Tile::tile_type()
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

double Tile::distanceTo(const Tile otherTile)
{
  return sqrt((otherTile.x() - _x)*(otherTile.x() - _x) + (otherTile.y() - _y) * (otherTile.y() - _y));
}
