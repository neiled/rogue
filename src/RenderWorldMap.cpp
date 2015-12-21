//
// Created by Neil Edwards on 12/20/15.
//

#include "RenderWorldMap.h"
#include "renderer.h"
#include "world.h"

RenderWorldMap::RenderWorldMap(Graphics *graphics) : _graphics(graphics)
{

}

void RenderWorldMap::render_map(Renderer &renderer,level_sprites_t tiles, SDL_Rect camera, World& world)
{
    for (int y = 0; y < world.height(); ++y) {
        for (int x = 0; x < world.width(); ++x) {
            if (y * Renderer::TILE_SIZE/4 < camera.y)
                continue;
            if (y * Renderer::TILE_SIZE/4 > camera.y + camera.h)
                continue;
            if (x * Renderer::TILE_SIZE/4 > camera.x + camera.w)
                continue;
            if (x * Renderer::TILE_SIZE/4 < camera.x)
                continue;

            auto currentTile = world.tile_type(x, y);
            int alpha = 255;
//
//
            draw_tile(&world, tiles, currentTile, x, y, camera.x, camera.y, alpha);
        }
    }
}

void RenderWorldMap::draw_tile(World* world, level_sprites_t sprites, TileType type, int x, int y,
                            int camerax, int cameray, int alpha)
{
    if(!_tile_sprites[y][x])
    {
        auto color = get_color(world->tile_min_height(), world->tile_max_height(), world->tile_height(x,y));
        auto symbol = get_symbol(world->tile_min_height(), world->tile_max_height(), world->tile_height(x, y));
        _tile_sprites[y][x] = new FontSprite(_graphics, symbol, Renderer::TILE_SIZE/4, color);

    }
//
    auto sprite = _tile_sprites[y][x];

    sprite->draw(x*Renderer::TILE_SIZE/4,y*Renderer::TILE_SIZE/4, camerax, cameray, alpha);
}


Sprite* RenderWorldMap::pick_sprite(level_sprites_t sprites, TileType type)
{
    auto random = Random::Between(0, static_cast<int>(sprites[type].size()-1));
    return sprites[type].at(random);
}

void RenderWorldMap::init()
{

}

SDL_Color RenderWorldMap::get_color(double min, double max, double height)
{
    double new_height = ((height-min)/(max-min));

    if(new_height < 0.3)
        return SDL_Color{(Uint8) (0 ), (Uint8) (25 * new_height/0.3 ), (Uint8) (255 * new_height/0.3)};
    else if(new_height < 0.6)
        return SDL_Color{(Uint8) (0 ), (Uint8) (255 * new_height/0.6), (Uint8) (21 * new_height/0.6 )};

    return SDL_Color{(Uint8) (255 * new_height), (Uint8) (255 * new_height), (Uint8) (255 * new_height)};


//    if(new_height < 0.2)
//        return SDL_Color{46,67,184};
//    else if(new_height < 0.4)
//        return SDL_Color{24, 94, 48};
//    else if(new_height < 0.5)
//        return SDL_Color{46, 184, 94};
//    else if(new_height < 0.6)
//        return SDL_Color{150, 150, 150};
//    else if(new_height < 0.7)
//        return SDL_Color{175, 175, 175};
//    else if(new_height < 0.8)
//        return SDL_Color{200, 200, 200};
//    else if(new_height < 0.9)
//        return SDL_Color{225, 225, 225};
//    else
//        return SDL_Color{255,255,255};

}

Uint16* RenderWorldMap::get_symbol(double min, double max, double height)
{
    double new_height = ((height-min)/(max-min));


    if(new_height < 0.3)
        return new Uint16[2] { L'\u079D', '\0' };
    else if(new_height < 0.6)
        return new Uint16[2] { L'\u1923', '\0' };
    else
        return new Uint16[2] { L'\u26C6', '\0' };

}