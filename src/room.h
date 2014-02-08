#ifndef ROOM_H
#define ROOM_H 


#include <vector>

using namespace std;

class Tile;

class Room
{
public:
  Room (int x, int y, int width, int height);
  virtual ~Room ();

  int getX();
  int getY();
  int getHeight();
  int getWidth();

  //double getFirstNeighbourDistance();
  //double getSecondNeihbourDistance();

  //void setFirstNeighbour(Room* room);
  //void setSecondNeighbour(Room* room);

  //Room* getFirstNeighbour();
  //Room* getSecondNeighbour();
  
  //void removeNeighbour(Room* room);
  void addNeighbour(Room* room);
  vector<Room*> getNeighbours();

  double distanceTo(Room* otherRoom);
  bool containsTile(Tile* tile);

private:
  /* data */
  int _x;
  int _y;
  int _width;
  int _height;
  vector<Room*> _neighbours;
  //Room* _neighbour1;
  //Room* _neighbour2;
  //double _n1Dist;
  //double _n2Dist;
};
#endif
