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
  _panel = _graphics->loadTexture("./content/blue_panel.png");
}
void RenderInventory::render_player_inventory(Renderer& renderer, item_sprites_t items, Inventory& inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 250;
  vp_inv.y = 50;
  vp_inv.h = 800;
  vp_inv.w = 800;

  int x = vp_inv.x+40;

  render(renderer, items, inventory.items(), vp_inv);
  renderer.render_string("Inventory:", x, vp_inv.y + 50, 32);
  renderer.render_string("To drop an item press d then the number", x, 750, 32);
  renderer.render_string("of the item to drop.", x, 782, 32);
}

void RenderInventory::render_player_wands(Renderer& renderer, item_sprites_t items, Inventory& inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 250;
  vp_inv.y = 50;
  vp_inv.h = 800;
  vp_inv.w = 800;

  int x = vp_inv.x+40;

  auto wands = inventory.items_of_type(ItemType::WAND);

  render(renderer, items, wands, vp_inv);
  renderer.render_string("Wands:", x, vp_inv.y + 50, 32);
  renderer.render_string("To zap a wand, press the number.", x, 750, 32);
}
void RenderInventory::render_chest_inventory(Renderer& renderer, item_sprites_t items, Inventory& inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 250;
  vp_inv.y = 50;
  vp_inv.h = 800;
  vp_inv.w = 800;

  int x = vp_inv.x + 40;

  render(renderer, items, inventory.items(), vp_inv);
  renderer.render_string("Chest Contents:", x, vp_inv.y+50, 32);
  renderer.render_string("To take an item press the number.", x, 750, 32);
  renderer.render_string("To take all items press the 'a' key.", x, 782, 32);
}

void RenderInventory::render(Renderer& renderer, item_sprites_t items, std::vector<Item*> inventory, SDL_Rect vp_inv)
{

  SDL_RenderCopy(_graphics->Renderer, _panel, NULL, &vp_inv);

  int count = 0;
  for(Item* item : inventory)
  {
    int x = vp_inv.x + 50;
    int y = vp_inv.y + (count * (Renderer::TILE_SIZE*1.5)) + 90;
    renderer.render_string(std::to_string(count) + ":", x, y, 32);
    items[item->item_type()][item->item_subtype()]->draw(x+Renderer::TILE_SIZE, y, 0, 0, SDL_ALPHA_OPAQUE);
    renderer.render_string(item->name(), x + Renderer::TILE_SIZE*3, y, 32);
    count++;
  }
}
