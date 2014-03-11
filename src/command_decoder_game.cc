#include "command_decoder_game.h"
#include "game_types.h"
#include "tile.h"
#include "messages.h"

bool CommandDecoderGame::Decode(SDL_Keycode key, Game& game)
{
  auto &player = *game.player();
  if(key == SDLK_UP || key == SDLK_KP_8)
    player.push_command(Commands::CMD::CMD_MOVE_UP);
  else if(key == SDLK_DOWN || key == SDLK_KP_2)
    player.push_command(Commands::CMD::CMD_MOVE_DOWN);
  else if(key == SDLK_LEFT || key == SDLK_KP_4)
    player.push_command(Commands::CMD::CMD_MOVE_LEFT);
  else if(key == SDLK_RIGHT || key == SDLK_KP_6)
    player.push_command(Commands::CMD::CMD_MOVE_RIGHT);
  else if(key == SDLK_o)
    player.push_command(Commands::CMD::CMD_EXPLORE);
  else if(key == SDLK_p)
    player.clearCommands();
  else if(key == SDLK_i)
    game.state(GameState::MENU_INVENTORY);
  else if(key == SDLK_PERIOD)
  {
    if(game.player()->chest())
      game.state(GameState::MENU_CHEST);
  }
  else if(key == SDLK_KP_5)
    player.push_command(Commands::CMD::NOP);
  else if(key == SDLK_ESCAPE)
    game.state(GameState::STOP);
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
      player.move_to(tile);
    else
      Messages::Push("It's too dangerous right now.");
  }
  return false;
}
