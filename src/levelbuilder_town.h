#ifndef LEVELBUILDER_TOWN_H_
#define LEVELBUILDER_TOWN_H_


#include <vector>

class Room;
class Level;
struct SDL_Point;
class Player;

class LevelBuilderTown
{
  public:
    LevelBuilderTown ();
    virtual ~LevelBuilderTown ();
    void buildLevel(Level& level, Player& player);

  private:
    void positionPlayer(Room& room, Player& player);

    std::vector<Room*> create_rooms(int amount, Level& level);
    Room* generateRoom(Level& level, int maxWidth, int maxHeight);
    bool roomFits(Room* room, Level& level);
    void digRoom(Room* room, Level& level);

    SDL_Point pickPointOfRoom(Room* room);
    Room* positionStairs(std::vector<Room*> rooms);

    void addDoors(Level& level);

    void generateMonsters(Level& level);

    const static int ROOM_HEIGHT = 8;
    const static int ROOM_WIDTH = 8;
};

#endif
