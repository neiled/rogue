#ifndef LEVEL_H_
#define LEVEL_H_

#include <iostream>
#include <array>
#include <vector>
#include "random.h"
#include "tile.h"

class Player;
class Monster;

class Level
{
  public:
    Level (int depth);
    virtual ~Level ();

    enum class LightType {
      Unseen, //player has no knowledge
      Unlit,  //player has seen but currently not lit
      Lit,    //player can currently see it and it's lit
      Revealed//player knows via magic but never actually seen it
    };

    void setType(int x, int y, TileType tileType);
    void update(Player& player);
    void updateGraphics();
    Level::LightType light_map(int x, int y);
    float light_intensity(int x, int y);
    Tile* tile(int x, int y);
    Tile* tile_of_type(TileType typeToLookFor);
    Tile* get_near_random_of_type(Tile&, int, TileType);
    Tile* get_near_random(Tile&, int);
    Tile* getRandomTileOfType(TileType typeToLookFor);
    std::vector<Monster*> getMonsters();
    void addMonster(Monster* monster);
    std::vector<Tile*> visible_tiles();
    int width();
    int height();
    
    Player* player();
    void set_player(Player* player);
    
    int depth();
    
    void reveal();

    const static int LEVEL_WIDTH = 100;
    const static int LEVEL_HEIGHT = 100;
    const static int LEVEL_ROOM_COUNT = 150;
    const static int LEVEL_MONSTER_COUNT = 75;
    const static int LEVEL_ITEM_COUNT = 25;
    const static int LEVEL_CHEST_COUNT = 5;

  private:
    int _depth; 

    void updateLightMap(Player& player);
    void resetLightMap();
    void update_monsters(Player& player);
    Tile* getRandomTile();
    
    std::array<std::array<Tile*, LEVEL_WIDTH>, LEVEL_HEIGHT > _map;
    std::array<std::array<Level::LightType, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _light_map;
    std::array<std::array<float, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _light_intensity;

    std::vector<Monster*> _monsters;
    Player* _player = nullptr;
  
};

typedef std::array<std::array<Level::LightType, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT> lightMap_t;

template <typename RandomGenerator = std::default_random_engine>
struct random_selector
{
  //On most platforms, you probably want to use std::random_device("/dev/urandom")()
  random_selector(RandomGenerator g = RandomGenerator(std::random_device()()))
    : gen(g) {}
 
  template <typename Iter>
  Iter select(Iter start, Iter end) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) -
