#ifndef A_STAR_H
#define A_STAR_H 

#include <vector>
#include <map>
#include <deque>

class Tile;
class Level;

class AStar
{
public:
  AStar ();
  virtual ~AStar ();

  std::deque<Tile*> plotPath(Tile& startingPoint, Tile& end, int max_count = -1);
  std::deque<Tile*> explore(Tile& startingPoint, Level& level);

private:
  std::vector<Tile*> open_list;
  std::vector<Tile*> closed_list;
  std::map<Tile*, Tile*> parentList;
  std::map<Tile*, int> gCost;

  std::vector<Tile*> surroundingValidTiles(Tile& startingPoint, bool avoid_monsters);
  Tile* findLowestScore(Tile& start, Tile* end);
  Tile* search(Tile& currentSquare, Tile* end);
  float score(Tile& start, Tile& end);
};
#endif
