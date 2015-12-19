//
// Created by Neil Edwards on 12/16/15.
//

#include <vector>
#include "FontSprite.h"

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, Uint16 *message, SDL_Color color, int size)
{
	TTF_Font *font = graphics->getFont("./content/unifont-8.0.01.ttf", 32);
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
	TTF_Font *font = graphics->getFont("./content/unifont-8.0.01.ttf", 32);
	if (font == nullptr)
	{
		auto error = TTF_GetError();
		throw std::runtime_error(std::string("Failed to load font: ") + error);
	}

	SDL_Surface *surf = get_surface(font, message, color, SDL_Color{ 0, 0, 0 });

	return generate_texture(graphics, surf, size);
}

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, SDL_Surface* surf, int size)
{
	SDL_SetRenderDrawColor(graphics->Renderer, 0x00, 0x00, 0x00, 0x00);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(graphics->Renderer, surf);
    SDL_Texture *t = SDL_CreateTexture(graphics->Renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, size, size);

	int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = size / 2 - iW / 2;
    int y = size / 2 - iH / 2;

    auto current_target = SDL_GetRenderTarget(graphics->Renderer);

    SDL_SetRenderTarget(graphics->Renderer, t);
	SDL_RenderFillRect(graphics->Renderer, NULL);
    graphics->renderTexture(texture, x, y);

    SDL_SetRenderTarget(graphics->Renderer, current_target);

    //Clean up unneeded stuff
    SDL_FreeSurface(surf);

    return t;
}


SDL_Surface *FontSprite::get_surface(TTF_Font* font, Uint16 *message, SDL_Color fg, SDL_Color bg)
{
	return TTF_RenderUNICODE_Shaded(font, message, fg, bg);
}

SDL_Surface *FontSprite::get_surface(TTF_Font* font, std::string message, SDL_Color fg, SDL_Color bg)
{
	return TTF_RenderText_Shaded(font, message.c_str(), fg, bg);
}
