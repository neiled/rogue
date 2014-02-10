#include "a_star.h"
#include "tile.h"
#include "level.h"

vector<Tile*> AStar::plotPath(Tile* startingPoint, Tile* end)
{
  open_list.push_back(startingPoint);

  vector<Tile*> otherTiles = surroundingValidTiles(startingPoint, closed_list);
  for(Tile* t : otherTiles)
    open_list.push_back(t);
  Tile* nextTile = bestPath(startingPoint, end, otherTiles);
  open_list.erase(remove(open_list.begin(), open_list.end(), nextTile), open_list.end());
  closed_list.push_back(nextTile);

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



