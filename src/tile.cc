#include "tile.h"
#include <cmath>
#include "actor.h"
#include <SDL2/SDL.h>

Tile::Tile(TileType tileType, Level& level, int x, int y) :_level(level)
{
  _tileType = tileType;
  _x = x;
  _y = y;
}

Tile::~Tile()
{
  SDL_Log("I'm being deleted! %d,%d", _x, _y);
}

void Tile::setActor(Actor& actor)
{
  _actor = &actor;
}

void Tile::removeActor()
{
  _actor= nullptr;
}

Actor* Tile::getActor()
{
  return _actor;
}

void Tile::setTileType(TileType tileType)
{
  _tileType = tileType;
}

Tile::TileType Tile::getTileType()
{
  return _tileType;
}

Level& Tile::getLevel()
{
  return _level;
}

int Tile::x() const
{
  return _x;
}


int Tile::y() const
{
  return _y;
}

double Tile::distanceTo(const Tile otherTile)
{
  return sqrt((otherTile.x() - _x)*(otherTile.x() - _x) + (otherTile.y() - _y) * (otherTile.y() - _y));
}
