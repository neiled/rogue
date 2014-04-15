#include <cmath>
#include <limits>
#include <cstddef>
#include "room.h"
#include "tile.h"
#include "level.h"
#include "random.h"

Room::Room(Level& level, int x, int y, int width, int height) : _level(level)
{
  _x = x;
  _y = y;
  _width = width;
  _height = height;
}

Room::~Room()
{
}

int Room::x()
{
  return _x;
}

int Room::y()
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

bool Room::containsTile(Tile* tile)
{
  if(!tile)
    return false;
  if(tile->x() < _x)
    return false;
  if(tile->x() >= _x + _width)
    return false;
  if(tile->y() < _y)
    return false;
  if(tile->y() >= _y + _height)
    return false;

  return true;
  
}

Tile* Room::getRandomTile(bool avoidWalls)
{
  int minX = avoidWalls ? 1 : 0;
  int maxX = avoidWalls ? _width-2 : _width-1;
  int minY = avoidWalls ? 1 : 0;
  int maxY = avoidWalls ? _height - 2 : _height - 1;

  int x = Random::Between(minX,maxX) + _x;
  int y = Random::Between(minY,maxY) + _y;

  return (_level.tile(x, y));
}

bool Room::dead_end()
{
  int door_count = 0;
  int wall_x = _x-1;
  int wall_y = _y-1;
  for(int y = wall_y; y <= _y + _height; ++y)
  {
    for(int x = wall_x; x <= _x + _width; ++x)
    {
      if((y == wall_y || y == _y + _height ) ||
         (x == wall_x || x == _x + _width ))
      {
        auto tile = _level.tile(x,y);
        if(tile && tile->tile_type() != TileType::Rock)
          door_count++;
        if(door_count > 1)
          return false;
      }

    }
  }
  return true;
}


double Room::distance_to(Room* otherRoom)
{
  return sqrt((otherRoom->x() - _x)*(otherRoom->x() - _x) + (otherRoom->y() - _y) * (otherRoom->y() - _y));
}
