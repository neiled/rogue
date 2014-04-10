#ifndef COMMAND_DECODER_WAND_H
#define COMMAND_DECODER_WAND_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>


class Item;

class CommandDecoderWand : public CommandDecoder
{
public:
  CommandDecoderWand();
  virtual bool Decode(SDL_Keycode key, Game& game) override;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;

private:
  std::vector<Item*> get_items(Player& player, GameState state);
  Item* get_item(std::vector<Item*> items, SDL_Keycode key);
  bool use_chosen_item(SDL_Keycode key, Game& game);

};
#endif
