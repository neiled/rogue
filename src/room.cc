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

std::vector<Room*> Room::getNeighbours()
{
  return _neighbours;
}

bool Room::containsTile(std::shared_ptr<Tile> tile)
{
  if(!tile)
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

std::shared_ptr<Tile> Room::getRandomTile(bool avoidWalls)
{
  int minX = avoidWalls ? 1 : 0;
  int maxX = avoidWalls ? _width-2 : _width-1;
  int minY = avoidWalls ? 1 : 0;
  int maxY = avoidWalls ? _height - 2 : _height - 1;

  int x = Random::Between(minX,maxX) + _x;
  int y = Random::Between(minY,maxY) + _y;

  return _level->getTile(x, y);
}


double Room::distanceTo(Room* otherRoom)
{
  return sqrt((otherRoom->getX() - _x)*(otherRoom->getX() - _x) + (otherRoom->getY() - _y) * (otherRoom->getY() - _y));
}
