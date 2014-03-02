#ifndef COMMAND_DECODER_DEAD_H
#define COMMAND_DECODER_DEAD_H 

#include "command_decoder.h"

class CommandDecoderDead : public CommandDecoder
{
public:
  virtual bool Decode(SDL_Keycode key, Game& game) override;

};
#endif
