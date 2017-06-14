//
// Created by Neil Edwards on 12/20/15.
//

#include <sstream>
#include "RenderWorldMap.h"
#include "renderer.h"

RenderWorldMap::RenderWorldMap(Graphics *graphics) : _graphics(graphics)
{

}

void RenderWorldMap::init()
{

}

void RenderWorldMap::generateTexture(World &world)
{
    SDL_Log("Generating Texture for World");
    int tile_size = Renderer::TILE_SIZE / 2;
    int t_height = world.height() * tile_size;
    int t_width = world.width() * tile_size;
    SDL_Log("Tile Size: %d", tile_size);
    SDL_Log("Total Width: %d", t_width);


    auto t = SDL_CreateTexture(_graphics->Renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, t_width, t_height);
    _heatMapGradient.createDefaultHeatMapGradient();
    auto current_target = SDL_GetRenderTarget(_graphics->Renderer);
    SDL_SetRenderTarget(_graphics->Renderer, t);
    SDL_RenderClear(_graphics->Renderer);
    std::map<std::string, FontSprite*> sprites;

    for (int y = 0; y < world.height(); ++y) {
        for (int x = 0; x < world.width(); ++x) {

            double height, min, max;
            height = world.tile_height(x, y);
            min = world.tile_min_height();
            max = world.tile_max_height();
            float new_height = (float) (2 * ((height - min) / (max - min)) - 1);

            float r, g, b;
            _heatMapGradient.getColorAtValue(new_height, r, g, b);

            auto color = SDL_Color{(Uint8) r, (Uint8) g,
                                       (Uint8) b};//get_color(world->tile_min_height(), world->tile_max_height(), world->tile_height(x,y));
            auto symbol = get_symbol(world.tile_min_height(), world.tile_max_height(), new_height);
            std::stringstream fmt;
            fmt << symbol[0] << color.r << color.g << color.b;
            auto key = fmt.str();
            if(sprites.find(key) == sprites.end())
            {
                auto new_s = new FontSprite(_graphics, symbol, tile_size, color);
                sprites[key] = new_s;

            }

            auto sprite = sprites[key];
            sprite->draw(x * tile_size, y * tile_size, 0, 0);
        }
    }
    sprites.clear();
    SDL_SetRenderTarget(_graphics->Renderer, current_target);
    full_map = new Sprite(_graphics, t, 0, 0, t_width, t_height);
    SDL_Log("Done.");
}

void RenderWorldMap::render_map(Renderer &renderer,double zoom, SDL_Rect camera, World* world)
{
    if (_seed != world->seed())
    {
        generateTexture(*world);
        _seed = world->seed();
    }
    full_map->draw(0 + camera.x, 0 + camera.y, camera.x, camera.y, camera.w, camera.h, 255, zoom);

}


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
    else if(height < 0.0625)
        return new Uint16[2] { L'\u0F02', '\0' }; //shore
    else if(height < 0.125)
        return new Uint16[2] { L'\u0634', '\0' }; //sand
    else if(height < 0.75)
        return new Uint16[2] { L'\u0729', '\0' }; //grass/dirt
    else
        return new Uint16[2] { L'\u071F', '\0' };

}
