#ifndef RENDER_LEVEL_H
#define RENDER_LEVEL_H 

#include <SDL2/SDL.h>
#include "game_types.h"
#include "level.h"

class Graphics;
class Renderer;
class Tile;

class RenderLevel
{
  public:
    RenderLevel(Graphics* graphics);
    void render(Renderer& renderer, SDL_Rect camera, level_sprites_t tiles, item_sprites_t items, Level& level);
    void render_items(item_sprites_t items, Tile& tile, SDL_Rect camera, int alpha);

  private:
    Graphics* _graphics;
    std::map<Level*, std::vector<std::vector<Sprite*> > > _tile_sprites;


    Sprite* pick_sprite(level_sprites_t sprites, TileType);
    void draw_tile(Level*, level_sprites_t, TileType, int, int, int, int, int);
};
#endif
