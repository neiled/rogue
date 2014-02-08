#ifndef ROOM_H
#define ROOM_H 


#include <vector>

using namespace std;

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
  vector<Room*> getNeighbours();

  double distanceTo(Room* otherRoom);
  bool containsTile(Tile* tile);
  Tile* getRandomTile();

private:
  Level* _level;
  int _x;
  int _y;
  int _width;
  int _height;
  vector<Room*> _neighbours;
};
#endif
