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
  //SDL_Log("Starting at: %d,%d", startingPoint->getX(), startingPoint->getY());
  //SDL_Log("Ending at: %d,%d", end->getX(), end->getY());
  
  Tile* nextTile = getNextSquare(startingPoint, end);
  //SDL_Log("First next Tile at: %d,%d", nextTile->getX(), nextTile->getY());

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
  open_list.push_back(currentSquare);
  //SDL_Log("Added %d,%d to open_list", currentSquare->getX(), currentSquare->getY());

  vector<Tile*> otherTiles = surroundingValidTiles(currentSquare, closed_list);
  for(Tile* t : otherTiles)
  {
    //SDL_Log("Added %d,%d to open_list", t->getX(), t->getY());
    open_list.push_back(t);
    parentList[t] = currentSquare;
    //SDL_Log("Parent of  %d,%d set to %d,%d", t->getX(), t->getY(), currentSquare->getX(), currentSquare->getY());
  }
  Tile* nextTile = bestPath(currentSquare, end, otherTiles);
  if(nextTile == nullptr)
    return nullptr;

  //SDL_Log("Best tile =  %d,%d", nextTile->getX(), nextTile->getY());
  
  open_list.erase(remove(open_list.begin(), open_list.end(), nextTile), open_list.end());
  closed_list.push_back(nextTile);  
  return nextTile;
}

Tile* AStar::bestPath(Tile* start, Tile* end, vector<Tile*> choices)
{
  float bestDistance = 10000000;
  Tile* bestTile = nullptr;
  for(Tile* currentTile : choices)
  {
    float distance = currentTile->distanceTo(end);
    if(distance < bestDistance)
    {
      bestDistance = distance;
      bestTile = currentTile;
    }
  }

  return bestTile;
}

vector<Tile*> AStar::surroundingValidTiles(Tile* start, vector<Tile*> closedList)
{
  vector<Tile*> result;
  int startX = start->getX();
  int startY = start->getY();
  for (int y = startY-1; y <= startY+1; ++y)
  {
    for (int x = startX-1; x <= startX+1; ++x)
    {
      if(x == y)
        continue;
      Tile* neighbour = start->getLevel()->getTile(x,y);
      if(find(closedList.begin(), closedList.end(), neighbour) != closedList.end())
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



