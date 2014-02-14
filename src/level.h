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

    enum class LightType {Unseen, Unlit, Lit};

    void setType(int x, int y, Tile::TileType tileType);
    void update(Player& player);
    void updateGraphics();
    Level::LightType getTileLightMap(int x, int y);
    Tile* getTile(int x, int y);
    Tile* getTileOfType(Tile::TileType typeToLookFor);
    Tile* getRandomTileOfType(Tile::TileType typeToLookFor);
    std::vector<Monster*> getMonsters();
    void addMonster(Monster* monster);
    
    Player* player();
    void set_player(Player* player);
    
    int getDepth();

    const static int LEVEL_WIDTH = 100;
    const static int LEVEL_HEIGHT = 100;
    const static int LEVEL_ROOM_COUNT = 150;
    const static int LEVEL_MONSTER_COUNT = 75;

  private:
    int _depth; 

    void updateLightMap(Player& player);
    void resetLightMap();
    Tile* getRandomTile();
    
    std::array<std::array<Tile*, LEVEL_WIDTH>, LEVEL_HEIGHT > _map;
    std::array<std::array<Level::LightType, Level::LEVEL_WIDTH>, Level::LEVEL_HEIGHT > _light_map;

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
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
  }
 
  //convenience function
  template <typename Iter>
  Iter operator()(Iter start, Iter end) {
    return select(start, end);
  }
 
  template <typename Container>
  auto operator()(const Container& c) -> decltype(*begin(c))& {
    return *select(begin(c), end(c));
  }
 
private:
  RandomGenerator gen;
};

#endif
