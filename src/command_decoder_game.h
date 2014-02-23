#ifndef COMMAND_DECODER_GAME_H
#define COMMAND_DECODER_GAME_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>

class CommandDecoderGame : public CommandDecoder
{
public:
  virtual void Decode(SDL_Keycode key, Game& game) override;

private:
  /* data */
};
#endif
