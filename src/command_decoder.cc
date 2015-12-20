#include "command_decoder.h"
#include "game_types.h"
#include <SDL2/SDL.h>
#include "item.h"


Item* CommandDecoder::get_item(std::vector<Item*> items, SDL_Keycode key)
{
  int index = get_index(key);
  if(index < 0)
    return nullptr;

  if(index >= items.size())
    return nullptr;

  return items.at(index);
}


int CommandDecoder::get_index(SDL_Keycode key)
{
  int index = -1;
  if(key == SDLK_0)
    index = 0;
  else if(key == SDLK_1)
    index = 1;
  else if(key == SDLK_2)
    index = 2;
  else if(key == SDLK_3)
    index = 3;
  else if(key == SDLK_4)
    index = 4;
  else if(key == SDLK_5)
    index = 5;
  else if(key == SDLK_6)
    index = 6;
  else if(key == SDLK_7)
    index = 7;
  else if(key == SDLK_8)
    index = 8;
  else if(key == SDLK_9)
    index = 9;

  return index;
}
