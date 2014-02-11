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

deque<Tile*> AStar::plotPath(Tile* startingPoint, Tile* end)
{
  deque<Tile*> results;

  open_list.push_back(startingPoint);
  gCost[startingPoint] = 0;
  
  Tile* nextTile = getNextSquare(end);
  
  while(nextTile != end)
  {
    nextTile = getNextSquare(nextTile, end);
    if(nextTile == nullptr)
    {
      SDL_Log("No way to get to square!");
      return deque<Tile*>();
    }
    //SDL_Log("Next Tile at: %d,%d", nextTile->getX(), nextTile->getY());
  }

  //SDL_Log("Last Tile at: %d,%d", nextTile->getX(), nextTile->getY());
  
  //now go through the parent list for each node building up the path
  while(nextTile != startingPoint)
  {
    results.push_front(nextTile);
    //SDL_Log("Current Tile: %d,%d", nextTile->getX(), nextTile->getY());
    nextTile = parentList[nextTile];

  }
  return results;
}

Tile* AStar::getNextSquare(Tile* currentSquare, Tile* end)
{
  Tile* nextTile = bestPath(currentSquare, end);
  open_list.erase(remove(open_list.begin(), open_list.end(), nextTile), open_list.end());
  closed_list.push_back(nextTile);  

  vector<Tile*> otherTiles = surroundingValidTiles(nextTile);
  for(Tile* t : otherTiles)
  {
    //if not on the open list
      if(find(open_list.begin(), open_list.end(), neighbour) == open_list.end())
      {
        gCost[t] = gCost[currentSquare] + 10;
        open_list.push_back(t);
        parentList[t] = currentSquare;        
      }
      else
      {
        if(gCost[t] > gCost[currentSquare] + 10)
        {
          gCost[t] = gCost[currentSquare] + 10;
          parentList[t] = currentSquare;
        }
      }
  }
  
  if(nextTile == nullptr)
    return nullptr;


  return nextTile;
}

Tile* AStar::bestPath(Tile* currentSquare, Tile* end)
{
  //float bestDistance = 10000000;
  Tile* bestTile = nullptr;
  float bestFScore = 0;
  for(Tile* currentTile : open_list)
  {
    float distance = currentTile->distanceTo(end);
    int gScore = gScore[currentSquare] + 10;
    float fScore = distance + gScore;
    if(fScore < bestFScore || bestFScore == 0)
    {
      bestFScore = fScore;
      bestTile = currentTile;
    }
  }

  return bestTile;
}

vector<Tile*> AStar::surroundingValidTiles(Tile* start)
{
  vector<Tile*> result;
  int startX = start->getX();
  int startY = start->getY();
  for (int y = startY-1; y <= startY+1; ++y)
  {
    for (int x = startX-1; x <= startX+1; ++x)
    {
      if(x != 0 && y != 0)
        continue;
      Tile* neighbour = start->getLevel()->getTile(x,y);
      if(find(closed_list.begin(), closed_list.end(), neighbour) != closed_list.end())
        continue;
      if(neighbour == nullptr)
        continue;
      if(neighbour->getTileType() == Tile::TileType::Rock)
        continue;
      result.push_back(neighbour);
    }
  }
  return result;
}



