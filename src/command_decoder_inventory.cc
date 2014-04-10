#include "command_decoder_inventory.h"
#include "game_types.h"
#include <SDL2/SDL.h>

CommandDecoderInventory::CommandDecoderInventory() : _drop_mode(false)
{
}

bool CommandDecoderInventory::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(GameState::GAME);
  else if(key == SDLK_i)
  {
    if(game.state() == GameState::MENU_INVENTORY)
      game.state(GameState::GAME);
    else
      game.state(GameState::MENU_INVENTORY);
  }
  else if(key == SDLK_w)
  {
    if(game.state() == GameState::MENU_WAND)
      game.state(GameState::GAME);
    else
      game.state(GameState::MENU_WAND);
  }
  else if(key == SDLK_d)
  {
    if(game.state() == GameState::MENU_INVENTORY)
      _drop_mode = !_drop_mode;
    return false;
  }
  else if(_drop_mode)
    return drop_chosen_item(key, game);
  else if(_drop_mode == false)
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

  game.state(GameState::GAME);
  return true;
}

std::vector<Item*> CommandDecoderInventory::get_items(Player& player, GameState state)
{
  if(state == GameState::MENU_INVENTORY)
    return player.inventory()->items();
  else if(state == GameState::MENU_WAND)
    return player.inventory()->items_of_type(ItemType::WAND);
  else
    return std::vector<Item*>();
}

Item* CommandDecoderInventory::get_item(std::vector<Item*> items, SDL_Keycode key)
{
  int index = get_index(key);
  if(index < 0)
    return nullptr;

  if(index > items.size())
    return nullptr;

  return items.at(index);
}

bool CommandDecoderInventory::drop_chosen_item(SDL_Keycode key, Game& game)
{
  auto items = get_items(*game.player(), game.state());
  auto item = get_item(items, key);

  if(!item)
    return false;

  game.player()->push_command(Commands::CMD::CMD_DROP, item, 200);

  _drop_mode = false;
  game.state(GameState::GAME);
  return true;
}

int CommandDecoderInventory::get_index(SDL_Keycode key)
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

//void CommandDecoderInventory::use_item(Player& player, int index)
//{
  //player.push_command(Commands::CMD::CMD_USE, player.inventory()->items()[index], 200);
//}
//void CommandDecoderInventory::drop_item(Player& player, int index)
//{
  //player.push_command(Commands::CMD::CMD_DROP, player.inventory()->items()[index]);
  //_drop_mode = false;
//}

bool CommandDecoderInventory::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}
