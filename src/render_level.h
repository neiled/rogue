#ifndef RENDER_LEVEL_H
#define RENDER_LEVEL_H 

#include <SDL2/SDL.h>
#include "game_types.h"

class Graphics;
class Renderer;
class Level;
class Tile;

class RenderLevel
{
  public:
    RenderLevel(Graphics* graphics);
    void render(Renderer& renderer, SDL_Rect camera, level_sprites_t tiles, item_sprites_t items, Level& level);
    void render_items(item_sprites_t items, Tile& tile, SDL_Rect camera, int alpha);

  private:
    Graphics* _graphics;
};
#endif
