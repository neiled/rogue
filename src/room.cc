#include "room.h"
#include <cmath>
#include <limits>
#include <cstddef>
#include "tile.h"

Room::Room(int x, int y, int width, int height)
{
  _x = x;
  _y = y;
  _width = width;
  _height = height;
  //_n1Dist = std::numeric_limits<double>::max();
  //_n2Dist = std::numeric_limits<double>::max();
  //_neighbour1 = nullptr;
  //_neighbour2 = nullptr;
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

//double Room::getFirstNeighbourDistance()
//{
  //return _n1Dist;
//}

//double Room::getSecondNeihbourDistance()
//{
  //return _n2Dist;
//}

//Room* Room::getFirstNeighbour()
//{
  //return _neighbour1;
//}


//Room* Room::getSecondNeighbour()
//{
  //return _neighbour2;
//}

//void Room::setFirstNeighbour(Room* room)
//{
  //_neighbour2 = _neighbour1;
  //_neighbour1 = room;

  //if(_neighbour1 != nullptr)
    //_n1Dist = distanceTo(_neighbour1);
  //if(_neighbour2 != nullptr)
    //_n2Dist = distanceTo(_neighbour2);
//}

//void Room::setSecondNeighbour(Room* room)
//{
  //_neighbour2 = room;
  //if(_neighbour2 != nullptr)
    //_n2Dist = distanceTo(_neighbour2);
//}

//void Room::removeNeighbour(Room* room)
//{
  //if(_neighbour1 == room)
    //_neighbour1 = nullptr;
  //else if(_neighbour2 == room)
    //_neighbour2 = nullptr;
//}

double Room::distanceTo(Room* otherRoom)
{
  return sqrt((otherRoom->getX() - _x)*(otherRoom->getX() - _x) + (otherRoom->getY() - _y) * (otherRoom->getY() - _y));
}
