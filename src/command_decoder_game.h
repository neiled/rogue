#ifndef COMMAND_DECODER_GAME_H
#define COMMAND_DECODER_GAME_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>
class Game;

class CommandDecoderGame : public CommandDecoder
{
public:
  virtual bool Decode(SDL_Keycode key, Game& game) override;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;

private:
  /* data */
};
#endif
