#include "render_ranged.h"
#include "renderer.h"
#include "game.h"
#include "player.h"

RenderRanged::RenderRanged(Graphics* g): _graphics(g)
{
}

RenderRanged::~RenderRanged()
{
}

void RenderRanged::init()
{
}

void RenderRanged::render(Renderer& renderer, Player& player)
{
  auto camera_rect = renderer.camera_rect();

  if(!player.level().look_tile())
    return;

  auto point = renderer.tile_to_screen(player.level().look_tile()->x(), player.level().look_tile()->y());
  SDL_Rect look;
  look.x = point.x;
  look.y = point.y;
  look.w = Renderer::TILE_SIZE;
  look.h = Renderer::TILE_SIZE;

  if(look.x > camera_rect.x + camera_rect.w-Renderer::TILE_SIZE)
    return;
  if(look.y > camera_rect.y + camera_rect.h-Renderer::TILE_SIZE)
    return;


  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(_graphics->Renderer, &look);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}
