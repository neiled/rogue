//
// Created by Neil Edwards on 12/20/15.
//

#ifndef ROGUE_RENDERWORLDMAP_H
#define ROGUE_RENDERWORLDMAP_H


#include "graphics.h"
#include "game_types.h"
#include "world.h"
#include "ColorGradient.h"

class Renderer;

class RenderWorldMap
{
public:
    RenderWorldMap(Graphics* graphics);
    void init();

    void render_map(Renderer &renderer, level_sprites_t tiles, SDL_Rect camera, World *world);

private:
    Graphics* _graphics;
    SDL_Texture* _panel;
    std::array<std::array<Sprite*, World::WORLD_HEIGHT>, World::WORLD_WIDTH> _tile_sprites;

    Uint16 *get_symbol(double min, double max, float height);
    ColorGradient _heatMapGradient;    // Used to create a nice array of different colors.

    Sprite *full_map;

    void generateTexture(World &world);

    int _seed;
};


#endif //ROGUE_RENDERWORLDMAP_H
