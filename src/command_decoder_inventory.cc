#include "command_decoder_inventory.h"
#include <SDL2/SDL.h>

bool CommandDecoderInventory::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(Game::GameState::GAME);
  else if(key == SDLK_i)
    game.state(Game::GameState::GAME);
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

void CommandDecoderInventory::use_item(Player& player, int index)
{
    player.inventory()->use(index, player);
    player.push_command(Commands::CMD::NOP);
}
