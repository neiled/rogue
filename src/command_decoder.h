#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H

#include <SDL2/SDL.h>
#include "commands.h"
#include "player.h"
#include "game.h"

class CommandDecoder
{
public:
  virtual bool Decode(SDL_Keycode key, Game& game) = 0;

};
#endif
