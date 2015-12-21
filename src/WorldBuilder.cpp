//
// Created by Neil Edwards on 12/20/15.
//

#include "WorldBuilder.h"
#include "PerlinNoise.h"
#include "world.h"

std::array<std::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH> WorldBuilder::build_world(World& world)
{
    std::array<std::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH > _map;

    double min = 1000;
    double max = -1000;

    PerlinNoise* p = new PerlinNoise(1, 5, 5, 4, 1);
    for (int y = 0; y < world.height(); ++y)
    {
        for (int x = 0; x < world.width(); ++x)
        {
            auto new_height = p->GetHeight((double)x/World::WORLD_WIDTH,(double)y/World::WORLD_HEIGHT);
            _map[y][x] = new_height;
            if(new_height < min)
                min = new_height;
            if(new_height > max)
                max = new_height;
        }
    }

    _min = min;
    _max = max;

    return _map;

}