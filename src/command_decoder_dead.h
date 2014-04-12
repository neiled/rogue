#ifndef COMMAND_DECODER_DEAD_H
#define COMMAND_DECODER_DEAD_H 

#include "command_decoder.h"

class Game;

class CommandDecoderDead : public CommandDecoder
{
public:
  virtual bool Decode(SDL_Keycode key, Game& game) override;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;

};
#endif
