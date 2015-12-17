//
// Created by Neil Edwards on 12/16/15.
//

#ifndef ROGUE_FONTSPRITE_H
#define ROGUE_FONTSPRITE_H


#include "sprite.h"

class FontSprite : public Sprite
{

public:
    FontSprite(Graphics *graphics, std::string symbol, int size, SDL_Color color) : Sprite(
            graphics, generate_texture(graphics, symbol, color, size), 0, 0, size, size)
    { }

    SDL_Texture *generate_texture(Graphics *graphics, std::string message, SDL_Color color, int size);
};


#endif //ROGUE_FONTSPRITE_H
