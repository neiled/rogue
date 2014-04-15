#ifndef ROOM_H
#define ROOM_H 


#include <vector>

class Tile;
class Level;

class Room
{
public:
  Room (Level& level, int x, int y, int width, int height);
  virtual ~Room ();

  int x();
  int y();
  int getHeight();
  int getWidth();

  void addNeighbour(Room* room);
  std::vector<Room*> getNeighbours();

  double distance_to(Room* otherRoom);
  bool containsTile(Tile* tile);
  Tile* getRandomTile(bool avoidWalls = false);

  bool dead_end();

private:
  Level& _level;
  int _x;
  int _y;
  int _width;
  int _height;
  std::vector<Room*> _neighbours;
};
#endif
