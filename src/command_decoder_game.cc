#include "command_decoder_game.h"

void CommandDecoderGame::Decode(SDL_Keycode key, Game& game)
{
  auto &player = *game.player();
  if(key == SDLK_UP)
    player.pushCommand(Commands::CMD::CMD_MOVE_UP);
  else if(key == SDLK_DOWN)
    player.pushCommand(Commands::CMD::CMD_MOVE_DOWN);
  else if(key == SDLK_LEFT)
    player.pushCommand(Commands::CMD::CMD_MOVE_LEFT);
  else if(key == SDLK_RIGHT)
    player.pushCommand(Commands::CMD::CMD_MOVE_RIGHT);
  else if(key == SDLK_o)
    player.pushCommand(Commands::CMD::CMD_EXPLORE);
  else if(key == SDLK_p)
    player.clearCommands();
  else if(key == SDLK_i)
    game.state(Game::GameState::MENU_INVENTORY);
  else if(key == SDLK_ESCAPE)
    game.state(Game::GameState::STOPPED);

}
