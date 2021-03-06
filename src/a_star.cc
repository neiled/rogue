#include "a_star.h"
#include "tile.h"
#include "level.h"
#include "actor.h"


AStar::AStar()
{
}

AStar::~AStar()
{

}

std::deque<Tile*> AStar::explore(Tile& startingPoint, Level& level)
{
  std::deque<Tile*> results;

  open_list.push_back(&startingPoint);

  Tile* unexploredTile = nullptr;

  Tile* result = &startingPoint;
  while(!unexploredTile)
  {
    result = search(*result, nullptr, false);
    if(!result)
    {
      return std::deque<Tile*>();
    }

    for(auto t : closed_list)
    {
      auto light_type = level.light_map(t->x(),t->y()); 
      if(light_type == Level::LightType::Unseen ||
         light_type == Level::LightType::Revealed)
      {
        unexploredTile = t;
        break;
      }
    }
  }

  //SDL_Log("Path of %d", closed_list.size());

  //compile reuslts
  while(unexploredTile != &startingPoint)
  {
    results.push_front(unexploredTile);
    unexploredTile = parentList[unexploredTile];
  }
  return results;
}


std::deque<Tile*> AStar::plotPath(Tile& startingPoint, Tile& end, int max_count, bool avoid_monsters)
{
  std::deque<Tile*> results;

  open_list.push_back(&startingPoint);
  gCost[&startingPoint] = 0;
  
  Tile* result = &startingPoint;
  while(find(closed_list.begin(), closed_list.end(), &end) == closed_list.end())
  {
    result = search(*result, &end, false);
    if(!result || (max_count >0 && closed_list.size() >= max_count))
    {
      SDL_Log("No way to get to square! List Count %d", closed_list.size());
      return std::deque<Tile*>();
    }
  }

  
  auto nextTile = &end;
  //now go through the parent list for each node building up the path
  while(nextTile != &startingPoint)
  {
    results.push_front(nextTile);
    nextTile = parentList[nextTile];
  }
  return results;
}

Tile* AStar::search(Tile& start, Tile* end, bool avoid_monsters)
{
  Tile* currentTile = findLowestScore(start, end);
  if(!currentTile)
    return nullptr;
  open_list.erase(remove(open_list.begin(), open_list.end(), currentTile), open_list.end());
  closed_list.push_back(currentTile);  

  std::vector<Tile*> otherTiles = surroundingValidTiles(*currentTile, avoid_monsters, end);
  for(auto t : otherTiles)
  {
    //if not on the open list
      if(find(open_list.begin(), open_list.end(), t) == open_list.end())
      {
        gCost[t] = gCost[currentTile] + 10;
        open_list.push_back(t);
        parentList[t] = currentTile;
      }
      else
      {
        if(gCost[t] > gCost[currentTile] + 10)
        {
          gCost[t] = gCost[currentTile] + 10;
          parentList[t] = currentTile;
        }
      }
  }
  


  return currentTile;
}

Tile* AStar::findLowestScore(Tile& currentSquare, Tile* end)
{
  Tile* bestTile = nullptr;
  float bestFScore = 0;
  for(auto currentTile : open_list)
  {
    float distance = 0;
    if(end)
      distance = score(currentSquare, *end);//currentTile->distanceTo(*end);
    int gScore = gCost[&currentSquare] + 10;
    float fScore = distance + gScore;
    if(fScore < bestFScore || bestFScore <= 0)
    {
      bestFScore = fScore;
      bestTile = currentTile;
    }
  }

  return bestTile;
}

float AStar::score(Tile& start, Tile& end)
{
  return abs(start.x() - end.x()) + abs(start.y() - end.y());
}

std::vector<Tile *> AStar::surroundingValidTiles(Tile& start, bool avoid_monsters, Tile* end)
{
  std::vector<Tile*> result;
  int startX = start.x();
  int startY = start.y();
  for (int offsety = -1; offsety <= 1; ++offsety)
  {
    for (int offsetx = -1; offsetx <= +1; ++offsetx)
    {
      if(offsetx != 0 && offsety != 0)
        continue;
      int x = startX + offsetx;
      int y = startY + offsety;
      auto neighbour = start.level().tile(x,y);
      if(!neighbour)
        continue;
      if(neighbour->tile_type() == TileType::Rock)
        continue;
      if(neighbour->tile_type() == TileType::StairsDown && (end != nullptr && end->tile_type() != TileType::StairsDown))
        continue;
      if(neighbour->tile_type() == TileType::StairsUp && (end != nullptr && end->tile_type() != TileType::StairsUp))
        continue;
      if(find(closed_list.begin(), closed_list.end(), neighbour) != closed_list.end())
        continue;
      if(avoid_monsters && neighbour->actor() && neighbour->actor()->is_player() == false) //avoid other monthers
        continue;
      result.push_back(neighbour);
    }
  }
  return result;
}



