#include "levelbuilder.h"
#include "tile.h"
#include "room.h"
#include "level.h"
#include <SDL2/SDL.h>
#include "random.h"


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

void LevelBuilder::buildLevel(Level* level, Player* player)
{
  random_selector<> selector{};

  vector<Room*> rooms = createRooms(75, level);

  connectRooms(rooms);

  digCorridors(rooms, level);

  Room* startRoom = positionStairs(rooms, level);

  positionPlayer(startRoom, player);
}

void LevelBuilder::positionPlayer(Room* room, Player* player)
{
  player->setCurrentTile(room->getRandomTile());
}

Room* LevelBuilder::positionStairs(vector<Room*> rooms, Level* level)
{
  int maxDistance = 0;
  Room* startRoom = nullptr;
  Room* endRoom = nullptr;
  
  for(Room* room : rooms)
  {
    for(Room* otherRoom : rooms)
    {
      int currentDistance = room->distanceTo(otherRoom);
      if(currentDistance > maxDistance)
      {
        startRoom = room;
        endRoom = otherRoom;
        maxDistance = currentDistance;
      }
    }
  }

  Tile* tile = startRoom->getRandomTile();
  tile->setTileType(Tile::TileType::StairsUp);

  SDL_Log("Putting stairs at %d,%d", tile->getX(), tile->getY());

  tile = endRoom->getRandomTile();
  tile->setTileType(Tile::TileType::StairsDown);

  SDL_Log("Putting stairs at %d,%d", tile->getX(), tile->getY());

  return startRoom;
}

void LevelBuilder::digCorridors(vector<Room*> rooms, Level* level)
{
  for(Room* startRoom : rooms)
  {
    for(Room* neighbour : startRoom->getNeighbours())
    {
      SDL_Point startPoint = pickPointOfRoom(startRoom);
      SDL_Point endPoint = pickPointOfRoom(neighbour);
  
      digCorridor(startPoint, endPoint, neighbour, level);
    }
  }
}

void LevelBuilder::connectRooms(vector<Room*> rooms)
{
  vector<Room*> connectedRooms;
  connectedRooms.push_back(rooms.front());

  do
  {
    double minDistance = 1000000;
    Room* startRoom = nullptr;
    Room* closestRoom = nullptr;
    for(Room* connectedRoom : connectedRooms)
    {
      for(Room* roomToTest : rooms)
      {
        if(std::find(connectedRooms.begin(), connectedRooms.end(), roomToTest) == connectedRooms.end())
        {
          if(closestRoom == nullptr)
          {
            closestRoom = roomToTest;
            minDistance = connectedRoom->distanceTo(roomToTest);
            startRoom = connectedRoom;
          }
          else if(roomToTest->distanceTo(connectedRoom) < minDistance)
          {
            closestRoom = roomToTest;
            minDistance = roomToTest->distanceTo(connectedRoom);
            startRoom = connectedRoom;
          }
          
        }
      }
    }
    startRoom->addNeighbour(closestRoom);
    connectedRooms.push_back(closestRoom);
  }while(connectedRooms.size() < rooms.size());

}

vector<Room*> LevelBuilder::createRooms(int amount, Level* level)
{
  vector<Room*> rooms;

  for (int i = 0; i < 50;)
  {
    Room* newRoom = generateRoom(level, 12, 12);

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
  Tile* tile = startRoom->getRandomTile();
  return SDL_Point {tile->getX(), tile->getY()};
  //int maxPoint = startRoom->getWidth() * 2 + startRoom->getHeight() * 2;
  //int pointPicked = Random::Between(0,maxPoint);

  //int x, y;
  //int w = startRoom->getWidth();
  //int h = startRoom->getHeight();
  
  //if(pointPicked <w)
  //{
    //x = pointPicked + startRoom->getX();
    //y = startRoom->getY();
  //}
  //else if(pointPicked < w + h)
  //{
    //x = w-1 + startRoom->getX();
    //y = pointPicked - w + startRoom->getY();
  //}
  //else if(pointPicked < 2*w + h)
  //{
    //x = 2*w-1 + h - pointPicked + startRoom->getX();
    //y = h-1 + startRoom->getY();
  //}
  //else
  //{
    //x = 0 + startRoom->getX();
    //y = 2*w-1 + 2*h - pointPicked + startRoom->getY();
  //}
  //return SDL_Point {x, y};
}

void LevelBuilder::digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level* level)
{
  if(startPoint.x == endPoint.x && startPoint.y == endPoint.y)
    return;

  bool moveY = Random::Between(0,1) == 1 && startPoint.y != endPoint.y;

  int xModifier = endPoint.x > startPoint.x ? 1 : -1;
  if(moveY || endPoint.x == startPoint.x)
    xModifier = 0;

  int yModifier = endPoint.y > startPoint.y ? 1 : -1;
  if(!moveY || endPoint.y == startPoint.y)
    yModifier = 0;

  int newX = startPoint.x + xModifier;
  int newY = startPoint.y + yModifier;

  Tile* tileToCheck = level->getTile(newX, newY);
  tileToCheck->setTileType(Tile::TileType::Floor);

  if(roomTarget->containsTile(level->getTile(newX+1, newY)))
    return;
  else if(roomTarget->containsTile(level->getTile(newX-1, newY)))
    return;
  else if(roomTarget->containsTile(level->getTile(newX, newY+1)))
    return;
  else if(roomTarget->containsTile(level->getTile(newX, newY-1)))
    return;
  else
    digCorridor(SDL_Point {newX, newY}, endPoint, roomTarget, level);
}



LevelBuilder::~LevelBuilder()
{
}

Room* LevelBuilder::generateRoom(Level* level, int maxWidth, int maxHeight)
{
  //std::uniform_int_distribution<int> dW(3,maxWidth);
  //std::uniform_int_distribution<int> dH(3,maxHeight);
  //std::uniform_int_distribution<int> dX(1,Level::LEVEL_WIDTH);
  //std::uniform_int_distribution<int> dY(1,Level::LEVEL_HEIGHT);
  //
  int width = Random::Between(3,maxWidth);
  int height = Random::Between(3, maxHeight);
  int x = Random::Between(1, Level::LEVEL_WIDTH);
  int y = Random::Between(1, Level::LEVEL_HEIGHT);

  //int width = dW(rd);
  //int height = dH(rd);

  //int x = dX(rd);
  //int y = dY(rd);

  return new Room(level, x, y, width, height);

}

bool LevelBuilder::roomFits(Room* room, Level* level)
{
  for (int y = room->getY()-1; y <= room->getY()+room->getHeight(); ++y)
  {
    for (int x = room->getX()-1; x <= room->getX()+room->getWidth(); ++x)
    {
      if(x >= Level::LEVEL_WIDTH-1)
        return false;
      if(y >= Level::LEVEL_HEIGHT-1)
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

