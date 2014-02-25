#ifndef RENDER_INVENTORY_H
#define RENDER_INVENTORY_H 

#include "game.h"

class Renderer;
class Inventory;

class RenderInventory
{
public:
  static void Render(Renderer& renderer, Graphics& graphics, Game::item_sprites_t items, Inventory& Inventory);

};
#endif
