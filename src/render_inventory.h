#ifndef RENDER_INVENTORY_H
#define RENDER_INVENTORY_H 

#include <SDL2/SDL.h>
#include "game_types.h"

class Renderer;
class Inventory;
class Sprite;
class Graphics;

class RenderInventory
{
public:
  RenderInventory(Graphics* graphics);
  void render(Renderer& renderer, item_sprites_t items, Inventory& Inventory);
  void init();
private:
  Graphics* _graphics;
  SDL_Texture* _panel;

};
#endif
