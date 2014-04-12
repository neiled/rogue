#include "command_decoder_wand.h"
#include "game_types.h"
#include <SDL2/SDL.h>
#include "player.h"
#include "game.h"
#include "wand.h"
#include "item.h"

CommandDecoderWand::CommandDecoderWand()
{
}

bool CommandDecoderWand::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(GameState::GAME);
  else if(key == SDLK_i)
  {
      game.state(GameState::MENU_INVENTORY);
  }
  else if(key == SDLK_w)
  {
    game.state(GameState::GAME);
  }
  else
    return use_chosen_item(key, game);

  return true;
}

bool CommandDecoderWand::use_chosen_item(SDL_Keycode key, Game& game)
{
  auto items = get_items(*game.player(), game.state());
  auto item = get_item(items, key);

  if(!item)
    return false;

  game.player()->ranged_weapon(static_cast<Wand*>(item));

  game.state(GameState::RANGED_TARGET);
  return true;
}

std::vector<Item*> CommandDecoderWand::get_items(Player& player, GameState state)
{
  return player.inventory()->items_of_type(ItemType::WAND);
}

bool CommandDecoderWand::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}
