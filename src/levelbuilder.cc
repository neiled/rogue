#include "levelbuilder.h"
#include "tile.h"
#include "room.h"
#include "level.h"
#include <SDL2/SDL.h>


template <typename RandomGenerator = std::default_random_engine>
struct random_selector
{
  //On most platforms, you probably want to use std::random_device("/dev/urandom")()
  random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
    : gen(g) {}
 
  template <typename Iter>
  Iter select(Iter start, Iter end) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
  }
 
  //convenience function
  template <typename Iter>
  Iter operator()(Iter start, Iter end) {
    return select(start, end);
  }
 
  template <typename Container>
  auto operator()(const Container& c) -> decltype(*begin(c))& {
    return *select(begin(c), end(c));
  }
 
private:
  RandomGenerator gen;
};

LevelBuilder::LevelBuilder()
{
}

void LevelBuilder::buildLevel(Level* level)
{
  random_selector<> selector{};

  vector<Room*> rooms = createRooms(50, level);

  connectRooms(rooms);


  for(Room* startRoom : rooms)
  {
    Room* endRoom = startRoom->getFirstNeighbour();

    SDL_Point startPoint = pickPointOfRoom(startRoom);
    SDL_Point endPoint = pickPointOfRoom(endRoom);

    digCorridor(startPoint, endPoint, level);

    endRoom = startRoom->getSecondNeighbour();
    
    startPoint = pickPointOfRoom(startRoom);
    endPoint = pickPointOfRoom(endRoom);

    digCorridor(startPoint, endPoint, level);
  }
}

void LevelBuilder::connectRooms(vector<Room*> rooms)
{
  for(Room* room : rooms)
  {
    for(Room* neighbour : rooms)
    {
      if(room != neighbour)
      {
        if(room->distanceTo(neighbour) < room->getFirstNeighbourDistance())
          room->setFirstNeighbour(neighbour);
        else if(room->distanceTo(neighbour) < room->getSecondNeihbourDistance())
          room->setSecondNeighbour(neighbour);
      }
    }
  }
}

vector<Room*> LevelBuilder::createRooms(int amount, Level* level)
{
  vector<Room*> rooms;
  //generate X number of rooms in the level
  //find all the rooms closest neighbours
  //plot a path to each neighbour

  for (int i = 0; i < 50;)
  {
    Room* newRoom = generateRoom(10, 10);

    if(roomFits(newRoom, level))
    {
      i++;
      digRoom(newRoom, level);
      rooms.push_back(newRoom);
    }
  }

  return rooms;
}

SDL_Point LevelBuilder::pickPointOfRoom(Room* startRoom)
{
  int maxPoint = startRoom->getWidth() * 2 + startRoom->getHeight() * 2;
  std::uniform_int_distribution<int> pointPicker(0,maxPoint);

  int pointPicked = pointPicker(rd);

  int x, y;
  int w = startRoom->getWidth();
  int h = startRoom->getHeight();
  
  if(pointPicked <w)
    return SDL_Point {pointPicked + startRoom->getX(), 0};
  if(pointPicked < w + h)
    return SDL_Point {w + startRoom->getX(), pointPicked - w + startRoom->getY()};
  if(pointPicked < 2*w + h)
    return SDL_Point {2*w + h - pointPicked + startRoom->getX(), h + startRoom->getY()};
  return SDL_Point{0 + startRoom->getX(), 2*w + 2*h - pointPicked + startRoom->getY()};
}

void LevelBuilder::digCorridor(SDL_Point startPoint, SDL_Point endPoint, Level* level)
{
  if(startPoint.x == endPoint.x && startPoint.y == endPoint.y)
    return;
  std::uniform_int_distribution<int> tossCoin(0,1);
  bool moveY = tossCoin(rd) == 1 && startPoint.y != endPoint.y;

  int xModifier = endPoint.x > startPoint.x ? 1 : -1;
  if(moveY || endPoint.x == startPoint.x)
    xModifier = 0;

  int yModifier = endPoint.y > startPoint.y ? 1 : -1;
  if(!moveY || endPoint.y == startPoint.y)
    yModifier = 0;

  int newX = startPoint.x + xModifier;
  int newY = startPoint.y + yModifier;

  //SDL_Log("New Pos %d,%d", newX, newY);

  Tile* tileToCheck = level->getTile(newX, newY);
  //if(tileToCheck->getTileType() != Tile::TileType::Floor)
  //{
    tileToCheck->setTileType(Tile::TileType::Floor);
    digCorridor(SDL_Point {newX, newY}, endPoint, level);
  //}
  //else
    //digCorridor(startPoint, endPoint, level);
  
}



LevelBuilder::~LevelBuilder()
{
}

Room* LevelBuilder::generateRoom(int maxWidth, int maxHeight)
{
  std::uniform_int_distribution<int> dW(2,maxWidth);
  std::uniform_int_distribution<int> dH(2,maxHeight);
  std::uniform_int_distribution<int> dX(2,Level::LEVEL_WIDTH);
  std::uniform_int_distribution<int> dY(2,Level::LEVEL_HEIGHT);

  int width = dW(rd);
  int height = dH(rd);

  int x = dX(rd);
  int y = dY(rd);

  return new Room(x, y, width, height);

}

bool LevelBuilder::roomFits(Room* room, Level* level)
{
  for (int y = room->getY(); y < room->getY()+room->getHeight(); ++y)
  {
    for (int x = room->getX(); x < room->getX()+room->getWidth(); ++x)
    {
      if(x >= Level::LEVEL_WIDTH)
        return false;
      if(y >= Level::LEVEL_HEIGHT)
        return false;

      if(level->getTile(x, y)->getTileType() == Tile::TileType::Floor)
        return false;
    }
    
  }
  return true;
}

void LevelBuilder::digRoom(Room* room, Level* level)
{
  for (int y = room->getY(); y < room->getY()+room->getHeight(); ++y)
  {
    for (int x = room->getX(); x < room->getX()+room->getWidth(); ++x)
    {
      level->getTile(x, y)->setTileType(Tile::TileType::Floor);
    }
  }
}

