#include "command_decoder_dead.h"


void CommandDecoderDead::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_y)
    game.state(Game::GameState::STARTING);
  if(key == SDLK_n)
    game.state(Game::GameState::STOP);
}
