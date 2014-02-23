#include "command_decoder_inventory.h"

void CommandDecoderInventory::Decode(SDL_Keycode key, Game& game)
{
  if(key == SDLK_ESCAPE)
    game.state(Game::GameState::GAME);
}
