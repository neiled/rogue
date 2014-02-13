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

  std::deque<std::shared_ptr<Tile>> plotPath(std::shared_ptr<Tile> startingPoint, std::shared_ptr<Tile> end);
  std::deque<std::shared_ptr<Tile>> explore(std::shared_ptr<Tile> startingPoint, Level* level);

private:
  std::vector<std::shared_ptr<Tile>> open_list;
  std::vector<std::shared_ptr<Tile> >closed_list;
  std::vector<std::shared_ptr<Tile>> surroundingValidTiles(std::shared_ptr<Tile> startingPoint);
  std::shared_ptr<Tile> findLowestScore(std::shared_ptr<Tile> start, std::shared_ptr<Tile> end);
  std::shared_ptr<Tile> search(std::shared_ptr<Tile> currentSquare, std::shared_ptr<Tile> end);
  std::map<std::shared_ptr<Tile>, std::shared_ptr<Tile>> parentList;
  std::map<std::shared_ptr<Tile>, int> gCost;
};
#endif
