#include "command_decoder_inventory.h"
#include "game.h"

CommandDecoderInventory::CommandDecoderInventory()
{
}

bool CommandDecoderInventory::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE || key == SDLK_i) {
    game.state(GameState::GAME);
    game.player()->inventory()->drop_mode(false);
  }
  else if(key == SDLK_w)
  {
    game.state(GameState::MENU_WAND);
  }
  else if(key == SDLK_d)
  {
    game.player()->inventory()->drop_mode(!game.player()->inventory()->drop_mode());
    return false;
  }
  else if(game.player()->inventory()->drop_mode())
    return drop_chosen_item(key, game);
  else
    return use_chosen_item(key, game);

  return true;
}

bool CommandDecoderInventory::use_chosen_item(SDL_Keycode key, Game& game)
{
  auto items = get_items(*game.player(), game.state());
  auto item = get_item(items, key);

  if(!item)
    return false;

  game.player()->push_command(Commands::CMD::CMD_USE, item, 200);

  return true;
}

std::vector<Item*> CommandDecoderInventory::get_items(Player& player, GameState state)
{
  return player.inventory()->items();
}

bool CommandDecoderInventory::drop_chosen_item(SDL_Keycode key, Game& game)
{
  auto items = get_items(*game.player(), game.state());
  auto item = get_item(items, key);

  if(!item)
    return false;

  game.player()->push_command(Commands::CMD::CMD_DROP, item, 200);

  return true;
}

bool CommandDecoderInventory::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}

