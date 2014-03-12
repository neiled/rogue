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
    void buildLevel(Level& level, Player& player);

  private:
    void positionPlayer(Room& room, Player& player);

    std::vector<Room*> create_rooms(int amount, Level& level);
    void connect_rooms(std::vector<Room*> rooms);
    Room* generateRoom(Level& level, int maxWidth, int maxHeight);
    bool roomFits(Room* room, Level& level);

    void digRoom(Room* room, Level& level);
    void digCorridor(SDL_Point startPoint, SDL_Point endPoint, Room* roomTarget, Level& level);
    void digCorridors(std::vector<Room*> rooms, Level& level);

    SDL_Point pickPointOfRoom(Room* room);
    Room* positionStairs(std::vector<Room*> rooms);

    void addDoors(Level& level);
    bool doorFits(int x, int y, Level& level);

    void generateMonsters(Level& level);
    void generate_items(Level& level);
    void generate_chests(Level& level, std::vector<Room*> rooms);

    const static int ROOM_HEIGHT = 8;
    const static int ROOM_WIDTH = 8;
};

#endif
