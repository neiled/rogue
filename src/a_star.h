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

  std::deque<Tile*> plotPath(Tile& startingPoint, Tile& end, int max_count = -1, bool avoid_monster = true);
  std::deque<Tile*> explore(Tile& startingPoint, Level& level);

private:
  std::vector<Tile*> open_list;
  std::vector<Tile*> closed_list;
  std::map<Tile*, Tile*> parentList;
  std::map<Tile*, int> gCost;

  std::vector<Tile *> surroundingValidTiles(Tile& startingPoint, bool avoid_monsters, Tile& pTile);
  Tile* findLowestScore(Tile& start, Tile* end);
  Tile* search(Tile& currentSquare, Tile* end, bool avoid_monsters);
  float score(Tile& start, Tile& end);

    std::vector<Tile *> surroundingValidTiles(Tile &start, bool avoid_monsters, Tile *end);
};
#endif
