#include "command_decoder_game.h"
#include "game_types.h"
#include "tile.h"

bool CommandDecoderGame::Decode(SDL_Keycode key, Game& game)
{
  auto &player = *game.player();
  if(key == SDLK_UP)
    player.push_command(Commands::CMD::CMD_MOVE_UP);
  else if(key == SDLK_DOWN)
    player.push_command(Commands::CMD::CMD_MOVE_DOWN);
  else if(key == SDLK_LEFT)
    player.push_command(Commands::CMD::CMD_MOVE_LEFT);
  else if(key == SDLK_RIGHT)
    player.push_command(Commands::CMD::CMD_MOVE_RIGHT);
  else if(key == SDLK_o)
    player.push_command(Commands::CMD::CMD_EXPLORE);
  else if(key == SDLK_p)
    player.clearCommands();
  else if(key == SDLK_i)
    game.state(GameState::MENU_INVENTORY);
  else if(key == SDLK_KP_5)
    player.push_command(Commands::CMD::NOP);
  else if(key == SDLK_ESCAPE)
    game.state(GameState::STOP);
  else return false;

  return true;

}

bool CommandDecoderGame::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  SDL_Log("Clicked at %d, %d", x, y);
  Tile* tile = game.get_tile_from_click(x, y);
  if(tile)
    SDL_Log("Tile Type: %d", tile->tile_type());
  return false;
}
