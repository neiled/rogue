#ifndef A_STAR_H
#define A_STAR_H 

#include <vector>
#include <map>
#include <deque>

class Tile;

using namespace std;

class AStar
{
public:
  AStar ();
  virtual ~AStar ();

  deque<Tile*> plotPath(Tile* startingPoint, Tile* end);

private:
  vector<Tile*> open_list;
  vector<Tile*> closed_list;
  vector<Tile*> surroundingValidTiles(Tile* startingPoint);
  Tile* findLowestScore(Tile* start, Tile* end);
  Tile* search(Tile* currentSquare, Tile* end);
  map<Tile*, Tile*> parentList;
  map<Tile*, int> gCost;
};
#endif
