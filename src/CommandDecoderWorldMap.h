//
// Created by Neil Edwards on 12/20/15.
//

#ifndef ROGUE_COMMANDDECODERWORLDMAP_H
#define ROGUE_COMMANDDECODERWORLDMAP_H


#include "command_decoder.h"

class CommandDecoderWorldMap : public CommandDecoder
{
public:
    virtual bool Decode(SDL_Keycode key, Game& game) override;
    virtual bool Decode(Uint8 button, Uint8 clicks, Sint32 x, Sint32 y, Game& game) override;
};


#endif //ROGUE_COMMANDDECODERWORLDMAP_H
