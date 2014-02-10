#ifndef A_STAR_H
#define A_STAR_H 

#include <vector>

class Tile;

using namespace std;

class AStar
{
public:
  AStar ();
  virtual ~AStar ();

  vector<Tile*> plotPath(Tile* startingPoint, Tile* end);

private:
  vector<Tile*> open_list;
  vector<Tile*> closed_list;
  vector<Tile*> surroundingValidTiles(Tile* startingPoint, vector<Tile*> closedList);
  Tile* bestPath(Tile* start, Tile* end, vector<Tile*> choices);
  
};
#endif
