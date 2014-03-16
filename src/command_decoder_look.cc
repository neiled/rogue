#include "command_decoder_look.h"

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

  return false;
  
}

bool CommandDecoderLook::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}
