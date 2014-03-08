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
    game.state(GameState::GAME);
  else if(key == SDLK_d)
  {
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
  if(key == SDLK_0)
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

bool CommandDecoderInventory::drop_chosen_item(SDL_Keycode key, Game& game)
{
  if(key == SDLK_0)
    drop_item(*game.player(), 0);
  else if(key == SDLK_1)
    drop_item(*game.player(), 1);
  else if(key == SDLK_2)
    drop_item(*game.player(), 2);
  else if(key == SDLK_3)
    drop_item(*game.player(), 3);
  else if(key == SDLK_4)
    drop_item(*game.player(), 4);
  else if(key == SDLK_5)
    drop_item(*game.player(), 5);
  else if(key == SDLK_6)
    drop_item(*game.player(), 6);
  else if(key == SDLK_7)
    drop_item(*game.player(), 7);
  else if(key == SDLK_8)
    drop_item(*game.player(), 8);
  else if(key == SDLK_9)
    drop_item(*game.player(), 9);
  else
    return false;

  return true;
}

void CommandDecoderInventory::use_item(Player& player, int index)
{
    player.inventory()->use(index, player);
    player.push_command(Commands::CMD::NOP);
}
void CommandDecoderInventory::drop_item(Player& player, int index)
{
    player.inventory()->drop(index, *player.tile());
    player.push_command(Commands::CMD::NOP);
    _drop_mode = false;
}

bool CommandDecoderInventory::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}
