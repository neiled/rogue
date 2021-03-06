//
// Created by Neil Edwards on 12/20/15.
//

#include "WorldBuilder.h"
#include "PerlinNoise.h"
#include "world.h"
#include "random.h"

std::array<std::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH> WorldBuilder::build_world(World& world)
{
    std::array<std::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH> _map = generate_base_world(world);

    return _map;

}

std::array<std::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH> WorldBuilder::generate_base_world(const World &world)
{
    std::__1::array<std::__1::array<double, World::WORLD_HEIGHT>, World::WORLD_WIDTH > _map;

    double min = 1000;
    double max = -1000;

    PerlinNoise* p = new PerlinNoise(0.7, 5, 2, 6, world.seed());
    for (int y = 0; y < world.height(); ++y)
    {
        for (int x = 0; x < world.width(); ++x)
        {
            auto new_height = p->GetHeight((double)x / World::WORLD_WIDTH, (double)y / World::WORLD_HEIGHT);
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