//
// Created by Neil Edwards on 12/16/15.
//

#ifndef ROGUE_FONTSPRITE_H
#define ROGUE_FONTSPRITE_H


#include "sprite.h"

class FontSprite : public Sprite
{

public:
    FontSprite(Graphics *graphics, Uint16 *message, int size, SDL_Color color) : Sprite(
            graphics, generate_texture(graphics, message, color, size), 0, 0, size, size)
    { }

	FontSprite(Graphics *graphics, std::string message, int size, SDL_Color color) : Sprite(
		graphics, generate_texture(graphics, message, color, size), 0, 0, size, size)
	{ }

	SDL_Texture *generate_texture(Graphics *graphics, std::string message, SDL_Color color, int size);
    SDL_Texture *generate_texture(Graphics *graphics, Uint16 *message, SDL_Color color, int size);
	SDL_Texture *generate_texture(Graphics *graphics, SDL_Surface *surf);
	SDL_Surface *get_surface(TTF_Font* font, Uint16 *message, SDL_Color fg, SDL_Color bg);
	SDL_Surface *get_surface(TTF_Font* font, std::string message, SDL_Color fg, SDL_Color bg);


	void draw(int x, int y, int offsetX, int offsetY, int alpha = 255);
};


#endif //ROGUE_FONTSPRITE_H
