#include "command_decoder_dead.h"


bool CommandDecoderDead::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_y)
    game.state(Game::GameState::STARTING);
  else if(key == SDLK_n)
    game.state(Game::GameState::STOP);
  else
    return false;

  return true;
}
