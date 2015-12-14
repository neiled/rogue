#include "command_decoder_game.h"
#include "game_types.h"
#include "tile.h"
#include "messages.h"
#include "level.h"
#include "game.h"

bool CommandDecoderGame::Decode(SDL_Keycode key, Game& game)
{
  auto &player = *game.player();
  if(key == SDLK_UP || key == SDLK_KP_8 || key == SDLK_k)
    player.push_command(Commands::CMD::CMD_MOVE_UP);
  else if(key == SDLK_DOWN || key == SDLK_KP_2 || key == SDLK_j)
    player.push_command(Commands::CMD::CMD_MOVE_DOWN);
  else if(key == SDLK_LEFT || key == SDLK_KP_4 || key == SDLK_h)
    player.push_command(Commands::CMD::CMD_MOVE_LEFT);
  else if(key == SDLK_RIGHT || key == SDLK_KP_6 || key == SDLK_l)
    player.push_command(Commands::CMD::CMD_MOVE_RIGHT);
  else if(key == SDLK_o)
    player.push_command(Commands::CMD::CMD_EXPLORE);
  else if(key == SDLK_i)
    player.push_command(Commands::CMD::CMD_STATE_INV, 0);
  else if(key == SDLK_w)
  {
    game.level()->look_tile(game.player()->tile());
    player.push_command(Commands::CMD::CMD_STATE_WAND, 0);
  }
  else if(key == SDLK_SLASH)
  {
    game.level()->look_tile(game.player()->tile());
    player.push_command(Commands::CMD::CMD_STATE_LOOK, 0);
  }
  else if(key == SDLK_PERIOD)
  {
    if(game.player()->chest())
      player.push_command(Commands::CMD::CMD_STATE_CHEST, 0);
  }
  else if(key == SDLK_KP_5 || key == SDLK_SPACE)
    player.push_command(Commands::CMD::NOP);
  else if(key == SDLK_ESCAPE)
    player.push_command(Commands::CMD::CMD_STATE_STOP);
  else return false;

  return true;

}

bool CommandDecoderGame::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  auto &player = *game.player();
  Tile* tile = game.get_tile_from_click(x, y);
  if(tile)
  {
    if(player.can_see_monster() == false)
    {
      player.move_to(tile);
      return true;
    }
    else
      Messages::Push("It's too dangerous right now.");
  }
  else
  {
    SDL_Log("No Tile Clicked");
  }
  return false;
}
