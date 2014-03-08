#ifndef RENDER_MONSTERS_H
#define RENDER_MONSTERS_H 


#include "game_types.h"

class Level;
class Renderer;

class RenderMonsters
{
public:
  static void Render(Renderer& renderer, monster_sprites_t monsters, Level& level);

};
#endif
