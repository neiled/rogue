#include <SDL2/SDL.h>
#include "levelbuilder.h"
#include "tile.h"
#include "room.h"
#include "level.h"
#include "player.h"
#include "monster.h"



LevelBuilder::LevelBuilder()
{
}

void LevelBuilder::buildLevel(Level* level, Player* player)
{

  std::vector<Room*> rooms = createRooms(75, level);

  connectRooms(rooms);

  digCorridors(rooms, level);

  Room* startRoom = positionStairs(rooms, level);

  positionPlayer(startRoom, player);

  generateMonsters(level);

  addDoors(level);
}

void LevelBuilder::generateMonsters(Level* level)
{
  for (int i = 0; i < Level::LEVEL_MONSTER_COUNT; ++i)
  {
    Tile* randomTile = level->getRandomTileOfType(Tile::TileType::Floor);
    Monster* monster = new Monster(randomTile, Monster::MonsterType::Orc, Monster::MonsterState::Awake);
    level->addMonster(monster);
    SDL_Log("Added monster to %d,%d", randomTile->getX(), randomTile->getY());
  }

}

void LevelBuilder::addDoors(Level* level)
{
  for(int y = 0; y < Level::LEVEL_HEIGHT-1; y++)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH-1; ++x)
    {
      if(doorFits(x, y, level))
          level->getTile(x, y)->setTileType(Tile::TileType::Door);
    }

  }
}

bool LevelBuilder::doorFits(int x, int y, Level* level)
{
  if(x <= 0 || y <= 0)
    return false;
  Tile* currentTile = level->getTile(x, y);
  if(currentTile->getTileType() != Tile::TileType::Floor)
    return false;
  if(level->getTile(x,y-1)->getTileType() == Tile::TileType::Floor)
  {
    if(level->getTile(x-1,y)->getTileType() != Tile::TileType::Rock)
      return false;
    if(level->getTile(x+1,y)->getTileType() != Tile::TileType::Rock)
      return false;
    if(level->getTile(x-1,y-1)->getTileType() != level->getTile(x+1,y-1)->getTileType())
      return false;
    if(level->getTile(x,y+1)->getTileType() != Tile::TileType::Floor)
      return false;
    if(level->getTile(x-1,y+1)->getTileType() != level->getTile(x+1,y+1)->getTileType())
      return false;
    return true;
  }
  else if(level->getTile(x-1, y)->getTileType() == Tile::TileType::Floor &&
      level->getTile(x+1, y)->getTileType() == Tile::TileType::Floor)
  {
    if(level->getTile(x, y-1)->getTileType() != Tile::TileType::Rock)
      return false;
    if(level->getTile(x, y+1)->getTileType() != Tile::TileType::Rock)
      return false;
    if(level->getTile(x-1,y-1)->getTileType() != level->getTile(x-1,y+1)->getTileType())
      return false;
    if(level->getTile(x+1,y-1)->getTileType() != level->getTile(x+1,y+1)->getTileType())
      return false;
    return true;
  }
  return false;
}

void LevelBuilder::positionPlayer(Room* room, Player* player)
{
  player->setCurrentTile(room->getRandomTile());
}

Room* LevelBuilder::positionStairs(std::vector<Room*> rooms, Level* level)
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

  Tile* tile = startRoom->getRandomTile(true);
  tile->setTileType(Tile::TileType::StairsUp);

  //SDL_Log("Putting stairs at %d,%d", tile->getX(), tile->getY());

  tile = endRoom->getRandomTile(true);
  tile->setTileType(Tile::TileType::StairsDown);

  //SDL_Log("Putting stairs at %d,%d", tile->getX(), tile->getY());

  return startRoom;
}

void LevelBuilder::digCorridors(std::vector<Room*> rooms, Level* level)
{
  for(Room* startRoom : rooms)
  {
    for(Room* neighbour : startRoom->getNeighbours())
    {
      SDL_Point startPoint = pickPointOfRoom(startRoom);
      SDL_Point endPoint = pickPointOfRoom(neighbour);
      if(startPoint.x == startRoom->getX()-1 && endPoint.x > startPoint.x + startRoom->getWidth())
        startPoint.x = startRoom->getX() + startRoom->getWidth();
      else if(startPoint.x == startRoom->getX() + startRoom->getWidth() && endPoint.x < startPoint.x)
        startPoint.x = startRoom->getX() -1 ;
      else if(startPoint.y == startRoom->getY()-1 && endPoint.y > startPoint.y + startRoom->getHeight())
        startPoint.y = startRoom->getY() + startRoom->getHeight();
      else if(startPoint.y == startRoom->getY() + startRoom->getHeight() && endPoint.y < startPoint.y )
        startPoint.y = startRoom->getY()-1;
  
      digCorridor(startPoint, endPoint, neighbour, level);
    }
  }
}

void LevelBuilder::connectRooms(std::vector<Room*> rooms)
{
  std::vector<Room*> connectedRooms;
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

std::vector<Room*> LevelBuilder::createRooms(int amount, Level* level)
{
  std::vector<Room*> rooms;

  for (int i = 0; i < LevelBuilder::ROOMS;)
  {
    Room* newRoom = generateRoom(level, LevelBuilder::ROOM_WIDTH, LevelBuilder::ROOM_HEIGHT);

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
  //Tile* tile = startRoom->getRandomTile();
  //return SDL_Point {tile->getX(), tile->getY()};
  int w = startRoom->getWidth();
  int h = startRoom->getHeight();
  int maxPoint = w* 2 + h* 2;
  int pointPicked = 0;
  do
  {
    pointPicked = Random::Between(0,maxPoint-2);
  }while(pointPicked == 0 || pointPicked == w-1 || pointPicked == w || pointPicked == w+h-1 || pointPicked == w+h|| pointPicked == w+w+h-1 || pointPicked == w+w+h);

  int x, y;
  
  if(pointPicked <w)
  {
    x = pointPicked + startRoom->getX();
    y = startRoom->getY()-1;
  }
  else if(pointPicked < w + h)
  {
    x = w + startRoom->getX();
    y = pointPicked - w + startRoom->getY();
  }
  else if(pointPicked < 2*w + h)
  {
    //x = 2*w-1 + h - pointPicked + startRoom->getX();
    //x = w - (pointPicked-w*2) + startRoom->getX();
    x = w + h + w -1 - pointPicked + startRoom->getX();
    y = h + startRoom->getY();
  }
  else
  {
    x = startRoom->getX() -1;
    y = 2*w-1 + 2*h - pointPicked + startRoom->getY();
  }
  //SDL_Log("Picked %d,%d after random %d picked. w: %d, h: %d - sp: %d,%d", x, y, pointPicked, w, h, startRoom->getX(), startRoom->getY());
  return SDL_Point {x, y};
}

void LevelBuilder::digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level* level)
{

  Tile* tileToCheck = level->getTile(startPoint.x, startPoint.y);
  tileToCheck->setTileType(Tile::TileType::Floor);
  int x = startPoint.x;
  int y = startPoint.y;

  if(startPoint.x == endPoint.x && startPoint.y == endPoint.y)
    return;
  if(roomTarget->containsTile(level->getTile(x+1, y)))
    return;
  else if(roomTarget->containsTile(level->getTile(x-1, y)))
    return;
  else if(roomTarget->containsTile(level->getTile(x, y+1)))
    return;
  else if(roomTarget->containsTile(level->getTile(x, y-1)))
    return;


  int xModifier = 0;
  int yModifier = 0;

  bool moveY = Random::Between(0,1) == 1 && startPoint.y != endPoint.y;

  xModifier = endPoint.x > startPoint.x ? 1 : -1;
  if(moveY || endPoint.x == startPoint.x)
    xModifier = 0;

  yModifier = endPoint.y > startPoint.y ? 1 : -1;
  if(!moveY || endPoint.y == startPoint.y)
    yModifier = 0;

  int newX = x + xModifier;
  int newY = y + yModifier;
  digCorridor(SDL_Point {newX, newY}, endPoint, roomTarget, level);
}



LevelBuilder::~LevelBuilder()
{
}

Room* LevelBuilder::generateRoom(Level* level, int maxWidth, int maxHeight)
{
  int width = Random::Between(3,maxWidth);
  int height = Random::Between(3, maxHeight);
  int x = Random::Between(1, Level::LEVEL_WIDTH);
  int y = Random::Between(1, Level::LEVEL_HEIGHT);

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

