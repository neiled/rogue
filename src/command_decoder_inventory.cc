#include "command_decoder_inventory.h"

void CommandDecoderInventory::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(Game::GameState::GAME);
  else if(key == SDLK_i)
    game.state(Game::GameState::GAME);
  else if(key == SDLK_0)
  {
    game.player()->inventory()->use(0);
    game.player()->push_command(Commands::CMD::NOP);
  }
}
