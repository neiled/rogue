#include "a_star.h"
#include "tile.h"
#include "level.h"
#include <SDL2/SDL.h>


AStar::AStar()
{
}

AStar::~AStar()
{

}

std::deque<Tile*> AStar::explore(Tile* startingPoint, Level* level)
{
  std::deque<Tile*> results;

  //SDL_Log("Starting at: %d,%d", startingPoint->getX(), startingPoint->getY());
  open_list.push_back(startingPoint);

  Tile* unexploredTile = nullptr;

  Tile* result = startingPoint;
  while(!unexploredTile)
  {
    result = search(result, nullptr);
    if(!result)
    {
      SDL_Log("Nowhere left to explore...");
      return std::deque<Tile*>();
    }

    for(Tile* t : closed_list)
    {
      if(level->getTileLightMap(t->getX(),t->getY()) == Level::LightType::Unseen)
      {
        unexploredTile = t;
        break;
      }
    }
  }

  //SDL_Log("Found a target of %d,%d", unexploredTile->getX(), unexploredTile->getY());
  //SDL_Log("Path of %d", closed_list.size());

  //compile reuslts
  while(unexploredTile != startingPoint)
  {
    results.push_front(unexploredTile);
    unexploredTile = parentList[unexploredTile];
  }
  return results;
}


std::deque<Tile*> AStar::plotPath(Tile* startingPoint, Tile* end)
{
  std::deque<Tile*> results;

  open_list.push_back(startingPoint);
  gCost[startingPoint] = 0;
  
  Tile* result = startingPoint;
  while(find(closed_list.begin(), closed_list.end(), end) == closed_list.end())
  {
    result = search(result, end);
    if(!result)
    {
      SDL_Log("No way to get to square!");
      return std::deque<Tile*>();
    }
  }

  
  Tile* nextTile = end;
  //now go through the parent list for each node building up the path
  while(nextTile != startingPoint)
  {
    results.push_front(nextTile);
    nextTile = parentList[nextTile];
  }
  return results;
}

Tile* AStar::search(Tile* currentTile, Tile* end)
{
  currentTile = findLowestScore(currentTile, end);
  if(!currentTile)
    return nullptr;
  open_list.erase(remove(open_list.begin(), open_list.end(), currentTile), open_list.end());
  closed_list.push_back(currentTile);  

  std::vector<Tile*> otherTiles = surroundingValidTiles(currentTile);
  for(Tile* t : otherTiles)
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

Tile* AStar::findLowestScore(Tile* currentSquare, Tile* end)
{
  Tile* bestTile = nullptr;
  float bestFScore = 0;
  for(Tile* currentTile : open_list)
  {
    float distance = 0;
    if(end)
      distance = currentTile->distanceTo(end);
    int gScore = gCost[currentSquare] + 10;
    float fScore = distance + gScore;
    if(fScore < bestFScore || bestFScore <= 0)
    {
      bestFScore = fScore;
      bestTile = currentTile;
    }
  }

  return bestTile;
}

std::vector<Tile*> AStar::surroundingValidTiles(Tile* start)
{
  std::vector<Tile*> result;
  int startX = start->getX();
  int startY = start->getY();
  for (int offsety = -1; offsety <= 1; ++offsety)
  {
    for (int offsetx = -1; offsetx <= +1; ++offsetx)
    {
      if(offsetx != 0 && offsety != 0)
        continue;
      int x = startX + offsetx;
      int y = startY + offsety;
      Tile* neighbour = start->getLevel()->getTile(x,y);
      if(!neighbour)
        continue;
      if(find(closed_list.begin(), closed_list.end(), neighbour) != closed_list.end())
        continue;
      if(neighbour->getTileType() == Tile::TileType::Rock)
        continue;
      result.push_back(neighbour);
    }
  }
  return result;
}



