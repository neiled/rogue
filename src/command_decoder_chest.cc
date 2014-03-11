#include "command_decoder_chest.h"
#include "chest.h"
#include "tile.h"
#include "game_types.h"
#include "messages.h"

CommandDecoderChest::CommandDecoderChest()
{
}

CommandDecoderChest::~CommandDecoderChest()
{
}

bool CommandDecoderChest::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(GameState::GAME);
  else if(key == SDLK_PERIOD)
    game.state(GameState::GAME);
  else if(key == SDLK_0)
    use_item(*game.player(), 0);
  else if(key == SDLK_1)
    use_item(*game.player(), 1);
  else if(key == SDLK_2)
    use_item(*game.player(), 2);
  else if(key == SDLK_3)
    use_item(*game.player(), 3);
  else if(key == SDLK_4)
    use_item(*game.player(), 4);
  else if(key == SDLK_5)
    use_item(*game.player(), 5);
  else if(key == SDLK_6)
    use_item(*game.player(), 6);
  else if(key == SDLK_7)
    use_item(*game.player(), 7);
  else if(key == SDLK_8)
    use_item(*game.player(), 8);
  else if(key == SDLK_9)
    use_item(*game.player(), 9);
  else
    return false;

  return true;

}

void CommandDecoderChest::use_item(Player& player, int index)
{
  if(player.inventory()->full())
  {
    Messages::Push("You cannot carry any more items.");
    return;
  }

  auto chosen_chest = player.chest();

  if(!chosen_chest)
    return;


  auto inv = chosen_chest->inventory();
  auto item = inv->remove(index);
  if(!item)
    return;

  player.inventory()->add(item);
  Messages::Add("You pick up the " + item->name());
}
