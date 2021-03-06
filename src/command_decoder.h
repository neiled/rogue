#ifndef COMMAND_DECODER_H
#define COMMAND_DECODER_H

#include <SDL2/SDL.h>
#include <vector>

class Item;
class Game;

class CommandDecoder
{
public:
  virtual bool Decode(SDL_Keycode key, Game& game) = 0;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) = 0;

protected:
  Item* get_item(std::vector<Item*> items, SDL_Keycode key);  
  int get_index(SDL_Keycode);
};
#endif
