//
// Created by Neil Edwards on 12/20/15.
//

#include "CommandDecoderMainMenu.h"
#include "game_types.h"
#include "commands.h"
#include "game.h"

bool CommandDecoderMainMenu::Decode(SDL_Keycode key, Game& game)
{
    auto &player = *game.player();
    if(key == SDLK_1) {
        game.state(GameState::STARTING);
        player.push_command(Commands::CMD::NOP);
    }
//    else if(key == SDLK_n) {
//        game.state(GameState::STOP);
//        player.push_command(Commands::CMD::NOP);
//    }
    else
        return false;

    return true;
}

bool CommandDecoderMainMenu::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
    return false;
}