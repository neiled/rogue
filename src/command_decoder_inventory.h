#ifndef COMMAND_DECODER_INVENTORY_H
#define COMMAND_DECODER_INVENTORY_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>

class CommandDecoderInventory : public CommandDecoder
{
public:
  virtual void Decode(SDL_Keycode key, Game& game) override;

private:
  /* data */
};
#endif
