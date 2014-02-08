#ifndef LEVELBUILDER_H_
#define LEVELBUILDER_H_


#include "levelbuilder.h"
#include <vector>

using namespace std;

class Room;
class Level;
class SDL_Point;
class Player;

class LevelBuilder
{
  public:
    LevelBuilder ();
    virtual ~LevelBuilder ();
    void buildLevel(Level* level, Player* player);

  private:

    vector<Room*> createRooms(int amount, Level* level);
    void connectRooms(vector<Room*> rooms);
    Room* generateRoom(Level* level, int maxWidth, int maxHeight);
    void digRoom(Room* room, Level* level);
    bool roomFits(Room* room, Level* level);
    SDL_Point pickPointOfRoom(Room* room);
    void digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level* level);
    void digCorridors(vector<Room*> rooms, Level* level);
    Room* positionStairs(vector<Room*> rooms, Level* level);
    void positionPlayer(Room* room, Player* player);

    const static int ROOMS = 150;
    const static int ROOM_HEIGHT = 8;
    const static int ROOM_WIDTH = 8;
};

#endif
