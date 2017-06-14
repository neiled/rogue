//
// Created by Neil Edwards on 12/20/15.
//

#include "RenderMainMenu.h"

#include "render_inventory.h"
#include "renderer.h"

RenderMainMenu::RenderMainMenu(Graphics* graphics) : _graphics(graphics)
{

}

void RenderMainMenu::init()
{
    SDL_Texture *t = SDL_CreateTexture(_graphics->Renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, 800, 800);


    auto current_target = SDL_GetRenderTarget(_graphics->Renderer);

    SDL_SetRenderTarget(_graphics->Renderer, t);
    SDL_SetRenderDrawColor(_graphics->Renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_graphics->Renderer);
    SDL_RenderFillRect(_graphics->Renderer, NULL);
    SDL_SetRenderDrawColor(_graphics->Renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(_graphics->Renderer, NULL);

    SDL_SetRenderTarget(_graphics->Renderer, current_target);

    _panel = t;
}
void RenderMainMenu::render_menu(Renderer& renderer)
{
    SDL_Rect vp_inv;
    vp_inv.x = 250;
    vp_inv.y = 50;
    vp_inv.h = 800;
    vp_inv.w = 800;

    int x = vp_inv.x+40;

    render(renderer, vp_inv);
    renderer.render_string("Main Menu:", x, vp_inv.y + 25, 32);
    renderer.render_string("1) Start New Game", x, vp_inv.y + 100, 32);
    renderer.render_string("2) Quit", x, vp_inv.y + 200, 32);
}

void RenderMainMenu::render(Renderer& renderer, SDL_Rect vp_inv)
{

    SDL_RenderCopy(_graphics->Renderer, _panel, NULL, &vp_inv);

//    int count = 0;
//    for(Item* item : inventory)
//    {
//        int x = vp_inv.x + 50;
//        int y = vp_inv.y + (count * (Renderer::TILE_SIZE*1.5)) + 90;
//        renderer.render_string(std::to_string(count) + ":", x, y, 32);
//        items[item->item_type()][item->item_subtype()]->draw(x+Renderer::TILE_SIZE, y, 0, 0, SDL_ALPHA_OPAQUE);
//        renderer.render_string(item->name(), x + Renderer::TILE_SIZE*3, y, 32);
//        count++;
//    }
}
