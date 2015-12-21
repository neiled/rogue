#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include "player.h"
#include "levelbuilder.h"
#include "WorldBuilder.h"

class Level;

class World
{
public:
    World();

    virtual ~World();

    void init();

    void update();

    void updateGraphics();

    int height() const;
    int width() const;




    TileType tile_type(int x, int y);
    double tile_height(int x, int y);
    double tile_min_height();
    double tile_max_height();

    Level *current_level();

    Player *player();

    const static int WORLD_WIDTH = 200;
    const static int WORLD_HEIGHT = 200;


private:
    void checkMoveLevel();

    Level *getLevel(int depth);

    Player _player;
    std::vector<Level *> _levels;
    LevelBuilder _levelBuilder;
    WorldBuilder _world_builder;
    std::array<std::array<double, WORLD_HEIGHT >, WORLD_WIDTH> _map;
};
#endif
