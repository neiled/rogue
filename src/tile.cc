#include "tile.h"
#include <cmath>
#include "actor.h"
#include <SDL2/SDL.h>

Tile::Tile()
{
  _tileType = TileType::Rock;
}

Tile::Tile(TileType tileType, Level* level, int x, int y)
{
  _tileType = tileType;
  _level = level;
  _x = x;
  _y = y;
}

Tile::~Tile()
{
  SDL_Log("I'm being deleted! %d,%d", _x, _y);
}

void Tile::setActor(Actor* actor)
{
  _actor = actor;
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

Level* Tile::getLevel()
{
  return _level;
}

int Tile::getX()
{
  return _x;
}

int Tile::getY()
{
  return _y;
}

double Tile::distanceTo(std::shared_ptr<Tile> otherRoom)
{
  return sqrt((otherRoom->getX() - _x)*(otherRoom->getX() - _x) + (otherRoom->getY() - _y) * (otherRoom->getY() - _y));
}
