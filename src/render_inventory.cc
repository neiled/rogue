#include "render_inventory.h"
#include "renderer.h"
#include "inventory.h"
#include "item.h"
#include "sprite.h"

RenderInventory::RenderInventory(Graphics* graphics) : _graphics(graphics)
{

}

void RenderInventory::init()
{
  _panel = _graphics->loadTexture("../content/blue_panel.png");
}

void RenderInventory::render(Renderer& renderer, item_sprites_t items, Inventory& inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 250;
  vp_inv.y = 50;
  vp_inv.h = 800;
  vp_inv.w = 800;

  SDL_RenderCopy(_graphics->Renderer, _panel, NULL, &vp_inv);
  
  int count = 0;
  for(Item* item : inventory.items())
  {
    int x = vp_inv.x + Renderer::TILE_SIZE;
    int y = vp_inv.y + (count * Renderer::TILE_SIZE) + 30;
    renderer.render_string(std::to_string(count), x, y+8, 16);
    items[item->item_type()][item->item_subtype()]->draw(x+Renderer::TILE_SIZE/2, y, 0, 0, SDL_ALPHA_OPAQUE);
    renderer.render_string(item->name(), x + Renderer::TILE_SIZE*2, y+8, 16);
    count++;
  }  
  renderer.render_string("To drop an item press d then", vp_inv.x + 30, 682, 32);
  renderer.render_string("the number of the item to drop.", vp_inv.x + 30, 714, 32);
}
