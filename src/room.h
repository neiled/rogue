#ifndef ROOM_H
#define ROOM_H 


class Room
{
public:
  Room (int x, int y, int width, int height);
  virtual ~Room ();

  int getX();
  int getY();
  int getHeight();
  int getWidth();

  double getFirstNeighbourDistance();
  double getSecondNeihbourDistance();

  void setFirstNeighbour(Room* room);
  void setSecondNeighbour(Room* room);

  Room* getFirstNeighbour();
  Room* getSecondNeighbour();
  
  void removeNeighbour(Room* room)

  double distanceTo(Room* otherRoom);

private:
  /* data */
  int _x;
  int _y;
  int _width;
  int _height;
  Room* _neighbour1;
  Room* _neighbour2;
  double _n1Dist;
  double _n2Dist;
};
#endif
