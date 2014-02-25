#include "render_inventory.h"
#include "renderer.h"
#include "inventory.h"
#include "item.h"
#include "sprite.h"

void RenderInventory::Render(Renderer& renderer, Graphics& graphics, Game::item_sprites_t items, Inventory& inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 100;
  vp_inv.y = 100;
  vp_inv.h = 800;
  vp_inv.w = 800;

  SDL_SetRenderDrawColor(graphics.Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(graphics.Renderer, &vp_inv);
  
  int count = 0;
  for(Item* item : inventory.items())
  {
    auto sprite =items[item->item_type()][item->item_subtype()]; 
    items[item->item_type()][item->item_subtype()]->draw(vp_inv.x + Renderer::TILE_SIZE, vp_inv.y + count*Renderer::TILE_SIZE, 0, 0, SDL_ALPHA_OPAQUE);
    renderer.render_string(std::to_string(count), vp_inv.x , vp_inv.y + 8 + (count * Renderer::TILE_SIZE), 16);
    renderer.render_string(item->name(), vp_inv.x + Renderer::TILE_SIZE*2, vp_inv.y + 8 + (count * Renderer::TILE_SIZE), 16);
    count++;
  }  
}
