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
  void render_actor_info(Renderer& renderer, Game&, Actor*, int start_y);
  void render_look(Renderer& renderer, Game& game, Player& player, int start_y);


private:
  Graphics* _graphics;
  Sprite* _info_char = nullptr;

  void render_string(Renderer& renderer, std::string, int y);
};
#endif
