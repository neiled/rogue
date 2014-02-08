#ifndef LEVELBUILDER_H_
#define LEVELBUILDER_H_


#include <random>
#include "levelbuilder.h"
#include <vector>

using namespace std;

class Room;
class Level;
class SDL_Point;

class LevelBuilder
{
  public:
    LevelBuilder ();
    virtual ~LevelBuilder ();
    void buildLevel(Level* level);

  private:
    std::random_device rd;

    vector<Room*> createRooms(int amount, Level* level);
    void connectRooms(vector<Room*> rooms);
    Room* generateRoom(int maxWidth, int maxHeight);
    void digRoom(Room* room, Level* level);
    bool roomFits(Room* room, Level* level);
    SDL_Point pickPointOfRoom(Room* room);
    void digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level* level);


};

#endif
