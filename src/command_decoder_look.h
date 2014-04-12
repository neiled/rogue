#ifndef COMMAND_DECODER_LOOK
#define COMMAND_DECODER_LOOK 

#include "command_decoder.h"
#include <SDL2/SDL.h>

class Game;
class Player;

class CommandDecoderLook : public CommandDecoder
{
public:
  CommandDecoderLook ();
  virtual ~CommandDecoderLook ();
  virtual bool Decode(SDL_Keycode key, Game& game) override;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;

private:
  void move_tile(Player& player, int x, int y);
  
};
#endif
