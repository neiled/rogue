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

  draw_line(renderer, *player.tile(), *player.level().look_tile());


  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(_graphics->Renderer, &look);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void RenderRanged::draw_line(Renderer& renderer, Tile& start, Tile& end)
{
  auto start_point = renderer.tile_to_screen(start.x(), start.y());
  start_point.x += Renderer::TILE_SIZE/2.0f;
  start_point.y += Renderer::TILE_SIZE/2.0f;
  auto end_point = renderer.tile_to_screen(end.x(), end.y());
  end_point.x += Renderer::TILE_SIZE/2.0f;
  end_point.y += Renderer::TILE_SIZE/2.0f;

  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(_graphics->Renderer, start_point.x, start_point.y, end_point.x, end_point.y);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

}
