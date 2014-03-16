#ifndef RENDER_INFO
#define RENDER_INFO 

#include <SDL2/SDL.h>
#include "game_types.h"

class Renderer;
class Sprite;
class Graphics;
class Game;
class Player;
class Actor;

class RenderInfo
{
public:
  RenderInfo (Graphics*);
  void init();
  void render(Renderer& renderer, Game& game, item_sprites_t items, SDL_Rect vp_info);
  void render_player_info(Renderer& renderer, Game&, Player&, item_sprites_t items);
  void render_actor_info(Renderer& renderer, Game&, Actor*);


private:
  Graphics* _graphics;
  Sprite* _info_char = nullptr;
};
#endif
