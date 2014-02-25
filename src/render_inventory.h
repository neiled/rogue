#ifndef RENDER_INVENTORY_H
#define RENDER_INVENTORY_H 

#include "game.h"
#include <SDL2/SDL.h>

class Renderer;
class Inventory;
class Sprite;

class RenderInventory
{
public:
  RenderInventory(Graphics* graphics);
  void render(Renderer& renderer, Game::item_sprites_t items, Inventory& Inventory);
private:
  Graphics* _graphics;
  SDL_Texture* _panel;

};
#endif
