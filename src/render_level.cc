#include "render_level.h"
#include "level.h"
#include "renderer.h"
#include "tile.h"
#include "item.h"
#include "sprite.h"


RenderLevel::RenderLevel(Graphics* graphics) : _graphics(graphics)
{
}

void RenderLevel::render(Renderer& renderer, SDL_Rect camera, level_sprites_t tiles, item_sprites_t items, Level& level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Level::LightType lit = level.light_map(x, y);
      if(lit == Level::LightType::Unseen)
        continue;
      if(y*Renderer::TILE_SIZE < camera.y)
        continue;
      if(y*Renderer::TILE_SIZE > camera.y + camera.h)
        continue;
      if(x*Renderer::TILE_SIZE > camera.x + camera.w)
        continue;
      if(x*Renderer::TILE_SIZE < camera.x)
        continue;

      auto currentTile = level.tile(x, y);
      auto tileType = currentTile->tile_type();
      int alpha = 255;

      if(lit == Level::LightType::Unlit)
        alpha = 100;
      else
      {
        auto intensity = level.light_intensity(x,y);
        alpha = static_cast<int>(255.0f * intensity);
        if(alpha < 128) alpha = 128;
      }

      tiles[tileType]->draw(x*Renderer::TILE_SIZE,y*Renderer::TILE_SIZE, camera.x, camera.y, alpha);
      if(lit == Level::LightType::Lit)
        render_items(items, *currentTile, camera, alpha);
    }
  }
}

void RenderLevel::render_items(item_sprites_t items, Tile& tile, SDL_Rect camera, int alpha)
{
  for(Item* item : tile.items())
  {
    items[item->item_type()][item->item_subtype()]->draw(tile.x()*Renderer::TILE_SIZE, tile.y()*Renderer::TILE_SIZE, camera.x, camera.y, alpha);
  }

}
