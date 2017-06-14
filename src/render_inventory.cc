#include "render_inventory.h"
#include "renderer.h"

RenderInventory::RenderInventory(Graphics* graphics) : _graphics(graphics)
{

}

void RenderInventory::init()
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
void RenderInventory::render_player_inventory(Renderer renderer, item_sprites_t items, Inventory &inventory)
{
  SDL_Rect vp_inv;
  vp_inv.x = 250;
  vp_inv.y = 50;
  vp_inv.h = 800;
  vp_inv.w = 800;

  int x = vp_inv.x+40;

  render(renderer, items, inventory.items(), vp_inv);
  renderer.render_string("Inventory:", x, vp_inv.y + 25, 32);
  if(inventory.drop_mode()) {
      renderer.render_string("Drop Mode!", x + 200, vp_inv.y + 25, 32);
      renderer.render_string("To drop an item press d then the number of", x, 750, 32);
      renderer.render_string("the item. To cancel dropping press 'd'", x, 782, 32);
  }
  else
  {
      renderer.render_string("To enter drop mode press 'd'.", x, 750, 32);
      renderer.render_string("To use an item press its number.", x, 782, 32);
  }
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
