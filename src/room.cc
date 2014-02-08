#include "room.h"
#include <cmath>
#include <limits>
#include <cstddef>
#include "tile.h"
#include "level.h"
#include "random.h"

Room::Room(Level* level, int x, int y, int width, int height)
{
  _level = level;
  _x = x;
  _y = y;
  _width = width;
  _height = height;
}

Room::~Room()
{
}

int Room::getX()
{
  return _x;
}

int Room::getY()
{
  return _y;
}

int Room::getHeight()
{
  return _height;
}

int Room::getWidth()
{
  return _width;
}

void Room::addNeighbour(Room* neighbour)
{
  _neighbours.push_back(neighbour);
}

vector<Room*> Room::getNeighbours()
{
  return _neighbours;
}

bool Room::containsTile(Tile* tile)
{
  if(tile == nullptr)
    return false;
  if(tile->getX() < _x)
    return false;
  if(tile->getX() >= _x + _width)
    return false;
  if(tile->getY() < _y)
    return false;
  if(tile->getY() >= _y + _height)
    return false;

  return true;
  
}

Tile* Room::getRandomTile()
{
  int x = Random::Between(0,_width-1) + _x;
  int y = Random::Between(0,_height-1) + _y;

  return _level->getTile(x, y);
}


double Room::distanceTo(Room* otherRoom)
{
  return sqrt((otherRoom->getX() - _x)*(otherRoom->getX() - _x) + (otherRoom->getY() - _y) * (otherRoom->getY() - _y));
}
