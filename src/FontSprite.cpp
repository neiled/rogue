//
// Created by Neil Edwards on 12/16/15.
//

#include <vector>
#include "FontSprite.h"

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, Uint16 *message, SDL_Color color, int size)
{
    auto font = graphics->getFont("./content/unifont-8.0.01.ttf", size);
	if (font == nullptr)
	{
		auto error = TTF_GetError();
		throw std::runtime_error(std::string("Failed to load font: ") + error);
	}

	SDL_Surface *surf = get_surface(font, message, color, SDL_Color{ 0, 0, 0 });

		return generate_texture(graphics, surf, size);
}

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, std::string message, SDL_Color color, int size)
{
    auto font = graphics->getFont("./content/unifont-8.0.01.ttf", size);
	if (font == nullptr)
	{
		auto error = TTF_GetError();
		throw std::runtime_error(std::string("Failed to load font: ") + error);
	}

    auto surf = get_surface(font, message, color, SDL_Color{0, 0, 0 });

	return generate_texture(graphics, surf, size);
}

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, SDL_Surface* surf, int size)
{
    auto texture = SDL_CreateTextureFromSurface(graphics->Renderer, surf);
    SDL_FreeSurface(surf);

    return texture;
}


SDL_Surface *FontSprite::get_surface(TTF_Font* font, Uint16 *message, SDL_Color fg, SDL_Color bg)
{
	return TTF_RenderUNICODE_Shaded(font, message, fg, bg);
}

SDL_Surface *FontSprite::get_surface(TTF_Font* font, std::string message, SDL_Color fg, SDL_Color bg)
{
	return TTF_RenderText_Shaded(font, message.c_str(), fg, bg);
}
