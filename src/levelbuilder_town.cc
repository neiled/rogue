#include <SDL2/SDL.h>
#include "levelbuilder_town.h"
#include "tile.h"
#include "room.h"
#include "level.h"
#include "player.h"
#include "monster.h"
#include "monster_factory.h"
#include "item_factory.h"
#include "chest.h"
#include <algorithm>


LevelBuilderTown::LevelBuilderTown()
{
}

void LevelBuilderTown::buildLevel(Level& level, Player& player)
{

  SDL_Log("Creating Rooms...");
  std::vector<Room*> rooms = create_rooms(Level::LEVEL_ROOM_COUNT, level);
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

  SDL_Log("Positioning Player...");
  positionPlayer(*startRoom, player);
  SDL_Log("Done.");

  for(auto current_room : rooms)
    delete current_room;
}

void LevelBuilderTown::generateMonsters(Level& level)
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

void LevelBuilderTown::addDoors(Level& level)
{

}


void LevelBuilderTown::positionPlayer(Room& room, Player& player)
{
  Tile* chosenTile;
  do
  {
    chosenTile = room.getRandomTile();
  }while(chosenTile->actor());

  player.set_tile(*chosenTile);
}

Room* LevelBuilderTown::positionStairs(std::vector<Room*> rooms)
{
  int maxDistance = 0;
  Room* startRoom = nullptr;
  Room* endRoom = nullptr;
  
  for(Room* room : rooms)
  {
    for(Room* otherRoom : rooms)
    {
      int currentDistance = room->distance_to(otherRoom);
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

std::vector<Room*> LevelBuilderTown::create_rooms(int amount, Level& level)
{
  std::vector<Room*> rooms;

  for (int i = 0; i < amount;)
  {
    Room* newRoom = generateRoom(level, LevelBuilderTown::ROOM_WIDTH, LevelBuilderTown::ROOM_HEIGHT);

    if(roomFits(newRoom, level))
    {
      i++;
      digRoom(newRoom, level);
      rooms.push_back(newRoom);
    }
  }

  return rooms;
}


LevelBuilderTown::~LevelBuilderTown()
{
}

Room* LevelBuilderTown::generateRoom(Level& level, int maxWidth, int maxHeight)
{
  int width = Random::Between(3,maxWidth);
  int height = Random::Between(3, maxHeight);
  int x = Random::Between(1, level.width());
  int y = Random::Between(1, level.height());

  return new Room(level, x, y, width, height);

}

bool LevelBuilderTown::roomFits(Room* room, Level& level)
{
  for (int y = room->y()-1; y <= room->y()+room->getHeight(); ++y)
  {
    for (int x = room->x()-1; x <= room->x()+room->getWidth(); ++x)
    {
      if(x >= level.width()-1)
        return false;
      if(y >= level.height()-1)
        return false;

      if(level.tile(x, y)->tile_type() == TileType::Floor)
        return false;
    }
  }
  return true;
}

void LevelBuilderTown::digRoom(Room* room, Level& level)
{
  for (int y = room->y(); y < room->y()+room->getHeight(); ++y)
  {
    for (int x = room->x(); x < room->x()+room->getWidth(); ++x)
    {
      level.tile(x, y)->setTileType(TileType::Floor);
    }
  }
}

