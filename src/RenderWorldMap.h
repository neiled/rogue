//
// Created by Neil Edwards on 12/20/15.
//

#ifndef ROGUE_RENDERWORLDMAP_H
#define ROGUE_RENDERWORLDMAP_H


#include "graphics.h"
#include "game_types.h"
#include "world.h"

class Renderer;

class RenderWorldMap
{
public:
    RenderWorldMap(Graphics* graphics);
    void init();
    void render_map(Renderer &renderer, level_sprites_t tiles, SDL_Rect camera, World &world);

private:
    Graphics* _graphics;
    SDL_Texture* _panel;
    std::array<std::array<Sprite*, World::WORLD_HEIGHT>, World::WORLD_WIDTH> _tile_sprites;

    Sprite *pick_sprite(level_sprites_t sprites, TileType type);

    void draw_tile(World *world, level_sprites_t sprites, TileType type, int x, int y, int camerax, int cameray, int alpha);

    SDL_Color get_color(double min, double max, double height);

    Uint16 *get_symbol(double min, double max, double height);
};


#endif //ROGUE_RENDERWORLDMAP_H
