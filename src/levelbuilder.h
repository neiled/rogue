#ifndef LEVELBUILDER_H_
#define LEVELBUILDER_H_


#include <vector>

class Room;
class Level;
struct SDL_Point;
class Player;

class LevelBuilder
{
  public:
    LevelBuilder ();
    virtual ~LevelBuilder ();
    void buildLevel(Level* level, Player* player);

  private:

    std::vector<Room*> createRooms(int amount, Level* level);
    void connectRooms(std::vector<Room*> rooms);
    Room* generateRoom(Level* level, int maxWidth, int maxHeight);
    void digRoom(Room* room, Level* level);
    bool roomFits(Room* room, Level* level);
    SDL_Point pickPointOfRoom(Room* room);
    void digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level* level);
    void digCorridors(std::vector<Room*> rooms, Level* level);
    Room* positionStairs(std::vector<Room*> rooms, Level* level);
    void positionPlayer(Room* room, Player* player);
    void addDoors(Level* level);
    bool doorFits(int x, int y, Level* level);
    void generateMonsters(Level* level);

    const static int ROOMS = 150;
    const static int ROOM_HEIGHT = 8;
    const static int ROOM_WIDTH = 8;
};

#endif
