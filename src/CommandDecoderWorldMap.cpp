//
// Created by Neil Edwards on 12/20/15.
//

#include "CommandDecoderWorldMap.h"
#include "game_types.h"
#include "commands.h"
#include "game.h"


bool CommandDecoderWorldMap::Decode(SDL_Keycode key, Game& game)
{
    auto &player = *game.player();
    if(key == SDLK_1) {
        game.state(GameState::STARTING);
        player.push_command(Commands::CMD::NOP);
    }
    else if(key == SDLK_ESCAPE) {
        player.push_command(Commands::CMD::NOP);
        game.state(GameState::STOP);
    }
    else if(key == SDLK_UP || key == SDLK_KP_8 || key == SDLK_k)
    {
        player.push_command(Commands::CMD::NOP);
        game.moveCamera(0, -MOVE_AMOUNT);
    }
    else if(key == SDLK_DOWN || key == SDLK_KP_2 || key == SDLK_j)
    {
        game.moveCamera(0, MOVE_AMOUNT);
        player.push_command(Commands::CMD::NOP);

    }
    else if(key == SDLK_LEFT || key == SDLK_KP_4 || key == SDLK_h)
    {
        game.moveCamera(-MOVE_AMOUNT, 0);
        player.push_command(Commands::CMD::NOP);

    }
    else if(key == SDLK_RIGHT || key == SDLK_KP_6 || key == SDLK_l)
    {
        game.moveCamera(MOVE_AMOUNT, 0);
        player.push_command(Commands::CMD::NOP);

    }
        else if(key == SDLK_PLUS || key == SDLK_KP_PLUS || key == SDLK_EQUALS)
    {
        game.increaseZoom(1);
    }
        else if(key == SDLK_MINUS)
    {
        game.decreaseZoom(1);
    }
    else
        return false;

    return true;
}

bool CommandDecoderWorldMap::Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game)
{
    return false;
}