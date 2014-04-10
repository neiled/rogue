#ifndef COMMAND_DECODER_INVENTORY_H
#define COMMAND_DECODER_INVENTORY_H 

#include "command_decoder.h"
#include <SDL2/SDL.h>


class Item;

class CommandDecoderInventory : public CommandDecoder
{
public:
  CommandDecoderInventory();
  virtual bool Decode(SDL_Keycode key, Game& game) override;
  virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;

protected:
  //void use_item(Player& player, int item);
  //void drop_item(Player& player, int item);

private:
  bool _drop_mode;
  std::vector<Item*> get_items(Player& player, GameState state);
  Item* get_item(std::vector<Item*> items, SDL_Keycode key);

  bool use_chosen_item(SDL_Keycode, Game&);
  bool drop_chosen_item(SDL_Keycode, Game&);
  int get_index(SDL_Keycode);
};
#endif
