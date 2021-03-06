//
// Created by Neil Edwards on 12/20/15.
//

#ifndef ROGUE_WORLDBUILDER_H
#define ROGUE_WORLDBUILDER_H


#include <array>

class World;

class WorldBuilder
{

public:
    std::array<std::array<double, 500>, 500> build_world(World &world);

    double max_height()
    {
        return _max;
    }

    double min_height()
    {
        return _min;
    }


private:
    double _min;
    double _max;

    std::array<std::array<double, 500>, 500> generate_base_world(const World &world);
};


#endif //ROGUE_WORLDBUILDER_H
