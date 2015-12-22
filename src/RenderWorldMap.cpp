//
// Created by Neil Edwards on 12/20/15.
//

#include "RenderWorldMap.h"
#include "renderer.h"
#include "world.h"
#include "ColorGradient.h"

RenderWorldMap::RenderWorldMap(Graphics *graphics) : _graphics(graphics)
{

}

void RenderWorldMap::init(World& world)
{
    int tile_size = Renderer::TILE_SIZE/4;
    int t_height = world.height() * tile_size;
    int t_width = world.width() * tile_size;

    auto t = SDL_CreateTexture(_graphics->Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, t_width, t_height);
    _heatMapGradient.createDefaultHeatMapGradient();
    auto current_target = SDL_GetRenderTarget(_graphics->Renderer);
    SDL_SetRenderTarget(_graphics->Renderer, t);
    SDL_RenderClear(_graphics->Renderer);
    for (int y = 0; y < world.height(); ++y) {
        for (int x = 0; x < world.width(); ++x) {

            double height, min, max;
            height = world.tile_height(x, y);
            min = world.tile_min_height();
            max = world.tile_max_height();
            float new_height = (float) (2 * ((height - min) / (max - min)) - 1);

            float r, g, b;
            _heatMapGradient.getColorAtValue(new_height, r, g, b);

            auto color = new SDL_Color{(Uint8) r, (Uint8) g,
                                       (Uint8) b};//get_color(world->tile_min_height(), world->tile_max_height(), world->tile_height(x,y));
            auto symbol = get_symbol(world.tile_min_height(), world.tile_max_height(), new_height);
            auto new_s = new FontSprite(_graphics, symbol, tile_size, *color);

            new_s->draw(x * tile_size, y * tile_size, 0, 0);
            delete new_s;
        }
    }
    SDL_SetRenderTarget(_graphics->Renderer, current_target);
    full_map = new Sprite(_graphics, t, 0, 0, t_width, t_height);

}

void RenderWorldMap::render_map(Renderer &renderer,level_sprites_t tiles, SDL_Rect camera, World& world)
{
    full_map->draw(0+camera.x, 0+camera.y, camera.x, camera.y, camera.w, camera.h, 255);

//    _graphics->renderTexture(full_map, -camera.x, -camera.y);

//    for (int y = 0; y < world.height(); ++y) {
//        for (int x = 0; x < world.width(); ++x) {
//            if (y * Renderer::TILE_SIZE/4 < camera.y)
//                continue;
//            if (y * Renderer::TILE_SIZE/4 > camera.y + camera.h)
//                continue;
//            if (x * Renderer::TILE_SIZE/4 > camera.x + camera.w)
//                continue;
//            if (x * Renderer::TILE_SIZE/4 < camera.x)
//                continue;
//
//            auto currentTile = world.tile_type(x, y);
//            int alpha = 255;
////
////
//            draw_tile(_heatMapGradient, currentTile, x, y, camera.x, camera.y, alpha);
//        }
//    }
}

void RenderWorldMap::draw_tile(ColorGradient& heatMapGradient, TileType type, int x, int y,
                            int camerax, int cameray, int alpha)
{
    auto sprite = _tile_sprites[y][x];
    sprite->draw(x*Renderer::TILE_SIZE/4,y*Renderer::TILE_SIZE/4, camerax, cameray, alpha);
}


//Sprite* RenderWorldMap::pick_sprite(level_sprites_t sprites, TileType type)
//{
//    auto random = Random::Between(0, static_cast<int>(sprites[type].size()-1));
//    return sprites[type].at(random);
//}



// SDL_Color RenderWorldMap::get_color(double min, double max, double height)
// {
//     double new_height = 2*((height-min)/(max-min))-1;




// //    if(new_height < 0.2)
// //        return SDL_Color{46,67,184};
// //    else if(new_height < 0.4)
// //        return SDL_Color{24, 94, 48};
// //    else if(new_height < 0.5)
// //        return SDL_Color{46, 184, 94};
// //    else if(new_height < 0.6)
// //        return SDL_Color{150, 150, 150};
// //    else if(new_height < 0.7)
// //        return SDL_Color{175, 175, 175};
// //    else if(new_height < 0.8)
// //        return SDL_Color{200, 200, 200};
// //    else if(new_height < 0.9)
// //        return SDL_Color{225, 225, 225};
// //    else
// //        return SDL_Color{255,255,255};

// }

Uint16* RenderWorldMap::get_symbol(double min, double max, float height)
{
//    color.push_back(ColorPoint(0, 0, 128,   -1.0f));      // deeps.
//    color.push_back(ColorPoint(0, 0, 255,   -0.25f));     // shallow.
//    color.push_back(ColorPoint(0, 128, 255,   0.0f));      // shore
//    color.push_back(ColorPoint(240, 240, 64,   0.0625f));     // sand.
//    color.push_back(ColorPoint(32, 160, 0,   0.1250f));     // grass.
//    color.push_back(ColorPoint(224, 224, 0,   0.375f));     // dirt.
//    color.push_back(ColorPoint(128, 128, 128,   0.75f));     // rock.
//    color.push_back(ColorPoint(255, 255, 255,   1.00f));     // snow.

    if(height < 0)
        return new Uint16[2] { L'\u079D', '\0' }; //water
    else if(height < 0.125)
        return new Uint16[2] { L'\u0F02', '\0' }; //sand
    else if(height < 0.75)
        return new Uint16[2] { L'\u1368', '\0' }; //grass/dirt
    else
        return new Uint16[2] { L'\u26C6', '\0' };

}
