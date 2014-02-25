#ifndef RENDER_MONSTERS_H
#define RENDER_MONSTERS_H 

#include "game.h"

class Level;
class Renderer;

class RenderMonsters
{
public:
  static void Render(Renderer& renderer, Game::monster_sprites_t monsters, Level& level);

};
#endif
