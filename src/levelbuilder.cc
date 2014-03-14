#include <SDL2/SDL.h>
#include "levelbuilder.h"
#include "tile.h"
#include "room.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "monster_factory.h"
#include "item_factory.h"
#include "chest.h"


LevelBuilder::LevelBuilder()
{
}

void LevelBuilder::buildLevel(Level& level, Player& player)
{

  SDL_Log("Creating Rooms...");
  std::vector<Room*> rooms = create_rooms(Level::LEVEL_ROOM_COUNT, level);
  SDL_Log("Done.");

  SDL_Log("Connecting Rooms...");
  connect_rooms(rooms);
  SDL_Log("Done.");

  SDL_Log("Digging Corridors...");
  digCorridors(rooms, level);
  SDL_Log("Done.");

  SDL_Log("Positioning Stairs...");
  Room* startRoom = positionStairs(rooms);
  SDL_Log("Done.");

  SDL_Log("Adding doors...");
  addDoors(level);
  SDL_Log("Done.");

  SDL_Log("Generating monsters...");
  generateMonsters(level);
  SDL_Log("Done.");

  SDL_Log("Generating items...");
  generate_items(level);
  SDL_Log("Done.");

  SDL_Log("Generating chests...");
  generate_chests(level, rooms);
  SDL_Log("Done.");

  SDL_Log("Positioning Player...");
  positionPlayer(*startRoom, player);
  SDL_Log("Done.");

  for(auto current_room : rooms)
    delete current_room;
}

void LevelBuilder::generate_items(Level& level)
{
  for (int i = 0; i < Level::LEVEL_ITEM_COUNT;)
  {
    auto randomTile = level.getRandomTileOfType(TileType::Floor);
    if(!randomTile->actor())
    {
      auto item = ItemFactory::Build(level.depth());
      randomTile->add_item(item);
      ++i;
    }
  }
}

void LevelBuilder::generate_chests(Level& level, std::vector<Room*> rooms)
{
  for(auto room : rooms)
  {
    if(room->dead_end() == false)
      continue;
    auto randomTile = room->getRandomTile();
    auto chest = static_cast<Chest*>(ItemFactory::Build(ItemType::CHEST, ItemSubtype::CHEST));
    while(true)
    {
      chest->inventory()->add(ItemFactory::Build(level.depth()));
      if(Random::CheckChance(50) == false)
        break;
    }
    randomTile->add_item(chest);
  }
}

void LevelBuilder::generateMonsters(Level& level)
{
  for (int i = 0; i < Level::LEVEL_MONSTER_COUNT;)
  {
    auto randomTile = level.getRandomTileOfType(TileType::Floor);
    if(!randomTile->actor())
    {
      auto monster = MonsterFactory::Build(*randomTile);
      level.addMonster(monster);
      ++i;
    }
  }
}

void LevelBuilder::addDoors(Level& level)
{
  for(int y = 0; y < Level::LEVEL_HEIGHT-1; y++)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH-1; ++x)
    {
      if(doorFits(x, y, level))
          level.tile(x, y)->setTileType(TileType::Door);
    }

  }
}

bool LevelBuilder::doorFits(int x, int y, Level& level)
{
  if(x <= 0 || y <= 0)
    return false;
  auto currentTile = level.tile(x, y);
  if(currentTile->tile_type() != TileType::Floor)
    return false;
  if(level.tile(x,y-1)->tile_type() == TileType::Floor)
  {
    if(level.tile(x-1,y)->tile_type() != TileType::Rock)
      return false;
    if(level.tile(x+1,y)->tile_type() != TileType::Rock)
      return false;
    if(level.tile(x-1,y-1)->tile_type() != level.tile(x+1,y-1)->tile_type())
      return false;
    if(level.tile(x,y+1)->tile_type() != TileType::Floor)
      return false;
    if(level.tile(x-1,y+1)->tile_type() != level.tile(x+1,y+1)->tile_type())
      return false;
    return true;
  }
  else if(level.tile(x-1, y)->tile_type() == TileType::Floor &&
      level.tile(x+1, y)->tile_type() == TileType::Floor)
  {
    if(level.tile(x, y-1)->tile_type() != TileType::Rock)
      return false;
    if(level.tile(x, y+1)->tile_type() != TileType::Rock)
      return false;
    if(level.tile(x-1,y-1)->tile_type() != level.tile(x-1,y+1)->tile_type())
      return false;
    if(level.tile(x+1,y-1)->tile_type() != level.tile(x+1,y+1)->tile_type())
      return false;
    return true;
  }
  return false;
}

void LevelBuilder::positionPlayer(Room& room, Player& player)
{
  Tile* chosenTile;
  do
  {
    chosenTile = room.getRandomTile();
  }while(chosenTile->actor());

  player.set_tile(*chosenTile);
}

Room* LevelBuilder::positionStairs(std::vector<Room*> rooms)
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

  auto startTile = startRoom->getRandomTile(true);
  startTile->setTileType(TileType::StairsUp);

  auto endTile = endRoom->getRandomTile(true);
  endTile->setTileType(TileType::StairsDown);

  return startRoom;
}

void LevelBuilder::digCorridors(std::vector<Room*> rooms, Level& level)
{
  for(Room* startRoom : rooms)
  {
    for(Room* neighbour : startRoom->getNeighbours())
    {
      SDL_Point startPoint = pickPointOfRoom(startRoom);
      SDL_Point endPoint = pickPointOfRoom(neighbour);
      if(startPoint.x == startRoom->x()-1 && endPoint.x > startPoint.x + startRoom->getWidth())
        startPoint.x = startRoom->x() + startRoom->getWidth();
      else if(startPoint.x == startRoom->x() + startRoom->getWidth() && endPoint.x < startPoint.x)
        startPoint.x = startRoom->x() -1 ;
      else if(startPoint.y == startRoom->y()-1 && endPoint.y > startPoint.y + startRoom->getHeight())
        startPoint.y = startRoom->y() + startRoom->getHeight();
      else if(startPoint.y == startRoom->y() + startRoom->getHeight() && endPoint.y < startPoint.y )
        startPoint.y = startRoom->y()-1;
  
      digCorridor(startPoint, endPoint, neighbour, level);
    }
  }
}

void LevelBuilder::connect_rooms(std::vector<Room*> rooms)
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
          if(!closestRoom)
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

std::vector<Room*> LevelBuilder::create_rooms(int amount, Level& level)
{
  std::vector<Room*> rooms;

  for (int i = 0; i < amount;)
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
    x = pointPicked + startRoom->x();
    y = startRoom->y()-1;
  }
  else if(pointPicked < w + h)
  {
    x = w + startRoom->x();
    y = pointPicked - w + startRoom->y();
  }
  else if(pointPicked < 2*w + h)
  {
    x = w + h + w -1 - pointPicked + startRoom->x();
    y = h + startRoom->y();
  }
  else
  {
    x = startRoom->x() -1;
    y = 2*w-1 + 2*h - pointPicked + startRoom->y();
  }
  return SDL_Point {x, y};
}

void LevelBuilder::digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level& level)
{

  auto tileToCheck = level.tile(startPoint.x, startPoint.y);
  tileToCheck->setTileType(TileType::Floor);
  int x = startPoint.x;
  int y = startPoint.y;

  if(startPoint.x == endPoint.x && startPoint.y == endPoint.y)
    return;
  if(roomTarget->containsTile(level.tile(x+1, y)))
    return;
  else if(roomTarget->containsTile(level.tile(x-1, y)))
    return;
  else if(roomTarget->containsTile(level.tile(x, y+1)))
    return;
  else if(roomTarget->containsTile(level.tile(x, y-1)))
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

Room* LevelBuilder::generateRoom(Level& level, int maxWidth, int maxHeight)
{
  int width = Random::Between(3,maxWidth);
  int height = Random::Between(3, maxHeight);
  int x = Random::Between(1, Level::LEVEL_WIDTH);
  int y = Random::Between(1, Level::LEVEL_HEIGHT);

  return new Room(level, x, y, width, height);

}

bool LevelBuilder::roomFits(Room* room, Level& level)
{
  for (int y = room->y()-1; y <= room->y()+room->getHeight(); ++y)
  {
    for (int x = room->x()-1; x <= room->x()+room->getWidth(); ++x)
    {
      if(x >= Level::LEVEL_WIDTH-1)
        return false;
      if(y >= Level::LEVEL_HEIGHT-1)
        return false;

      if(level.tile(x, y)->tile_type() == TileType::Floor)
        return false;
    }
  }
  return true;
}

void LevelBuilder::digRoom(Room* room, Level& level)
{
  for (int y = room->y(); y < room->y()+room->getHeight(); ++y)
  {
    for (int x = room->x(); x < room->x()+room->getWidth(); ++x)
    {
      level.tile(x, y)->setTileType(TileType::Floor);
    }
  }
}

