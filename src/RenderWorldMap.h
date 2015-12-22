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
    void render_map(Renderer &renderer, level_sprites_t tiles, SDL_Rect camera, World &world);
    void init(World &world);

private:
    Graphics* _graphics;
    SDL_Texture* _panel;
    std::array<std::array<Sprite*, World::WORLD_HEIGHT>, World::WORLD_WIDTH> _tile_sprites;

//    Sprite *pick_sprite(level_sprites_t sprites, TileType type);
//    void draw_tile(World *world, level_sprites_t sprites, TileType type, int x, int y, int camerax, int cameray, int alpha);

//    SDL_Color get_color(double min, double max, double height);

//    Uint16 *get_symbol(double min, double max, double height);

//    void draw_tile(World *world, ColorGradient &heatMapGradient, level_sprites_t sprites, TileType type, int x, int y, int camerax, int cameray, int alpha);

    Uint16 *get_symbol(double min, double max, float height);
    ColorGradient _heatMapGradient;    // Used to create a nice array of different colors.
    void draw_tile(ColorGradient &heatMapGradient, TileType type, int x, int y, int camerax, int cameray, int alpha);

    Sprite *full_map;

};


#endif //ROGUE_RENDERWORLDMAP_H
