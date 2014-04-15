#include "command_decoder_look.h"
#include "level.h"
#include "player.h"
#include "game.h"
#include "ranged_weapon.h"

CommandDecoderLook::CommandDecoderLook()
{
}

CommandDecoderLook::~CommandDecoderLook()
{
}

bool CommandDecoderLook::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(GameState::GAME);
  else if(key == SDLK_SLASH)
    game.state(GameState::GAME);
  else if(key == SDLK_UP || key == SDLK_KP_8)
    move_tile(*game.player(), 0,-1);
  else if(key == SDLK_DOWN || key == SDLK_KP_2)
    move_tile(*game.player(), 0,1);
  else if(key == SDLK_LEFT || key == SDLK_KP_4)
    move_tile(*game.player(), -1,0);
  else if(key == SDLK_RIGHT || key == SDLK_KP_6)
    move_tile(*game.player(), 1,0);
  else if(key == SDLK_RETURN)
  {
    if(game.state() == GameState::LOOK)
      game.state(GameState::GAME);
    else if(game.state() == GameState::RANGED_TARGET)
    {
      if(game.player()->ranged_weapon())
      {
        game.player()->ranged_weapon()->fire(*game.player(), *game.player()->level().look_tile());
      }
      game.state(GameState::GAME);
    }
  }
  else return false;

  return true;
  
}

bool CommandDecoderLook::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  Tile* tile = game.get_tile_from_click(x, y);
  if(tile)
  {
    game.player()->level().look_tile(tile);
    return true;
  }
  else
    return false;
}

void CommandDecoderLook::move_tile(Player& player, int x, int y)
{
  Tile* current_tile = player.level().look_tile();

  int new_x = current_tile->x() + x;
  int new_y = current_tile->y() + y;

  if(new_x < 0) new_x = 0;
  if(new_y < 0) new_y = 0;
  if(new_x >= player.level().width())
    new_x = player.level().width()-1;
  if(new_y >= player.level().height())
    new_y = player.level().height()-1;

  player.level().look_tile(player.level().tile(new_x, new_y));
}
