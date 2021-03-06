#include "command_decoder_dead.h"
#include "game_types.h"
#include "game.h"


bool CommandDecoderDead::Decode(SDL_Keycode key, Game& game)
{
  auto &player = *game.player();
  if(key == SDLK_y) {
    game.state(GameState::STARTING);
    player.push_command(Commands::CMD::NOP);
  }
  else if(key == SDLK_n) {
    game.state(GameState::STOP);
    player.push_command(Commands::CMD::NOP);
  }
  else
    return false;

  return true;
}

bool CommandDecoderDead::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
  return false;
}
