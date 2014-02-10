#include "a_star.h"
#include "tile.h"
#include "level.h"

/*
struct StarNode
{
  public:
  StarNode(Tile* tile, StarNode parentNode)
  {
    parent = parentNode;
    _tile = tile;
  }
  
  double getH(Tile* destination)
  {
    return tile->distanceTo(destination);
  }
  
  int getG()
  {
    return 1;
  }
  
  double getF(Tile* destination)
  {
    return getG()+getH();
  }
  
  
  StarNode* parent;
  
  private:
  Tile* _tile;
};
*/
vector<Tile*> AStar::plotPath(Tile* startingPoint, Tile* end)
{
  map<Tile*, Tile*> parentList;
  
  Tile* nextTile = getNextSquare(startingPoint)

  while(nextTile != end)
  {
    nextTile = getNextSquare(nextTile);
  }
  
  //now go through the parent list for each node building up the path

}

Tile* AStar::getNextSquare(Tile* currentSquare)
{
  open_list.push_back(currentSquare);

  vector<Tile*> otherTiles = surroundingValidTiles(currentSquare, closed_list);
  for(Tile* t : otherTiles)
  {
    open_list.push_back(t);
    parentList[t] = currentSquare;
  }
  Tile* nextTile = bestPath(currentSquare, end, otherTiles);
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



