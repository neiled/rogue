#ifndef ROOM_H
#define ROOM_H 


#include <vector>

class Tile;
class Level;

class Room
{
public:
  Room (Level* level, int x, int y, int width, int height);
  virtual ~Room ();

  int getX();
  int getY();
  int getHeight();
  int getWidth();

  void addNeighbour(Room* room);
  std::vector<Room*> getNeighbours();

  double distanceTo(Room* otherRoom);
  bool containsTile(std::shared_ptr<Tile> tile);
  std::shared_ptr<Tile> getRandomTile(bool avoidWalls = false);

private:
  Level* _level = nullptr
  int _y;
  int _width;
  int _height;
  std::vector<Room*> _neighbours;
};
#endif
