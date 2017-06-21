//
// Created by Neil Edwards on 12/16/15.
//

#include <vector>
#include "FontSprite.h"
#include "renderer.h"

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, Uint16 *message, SDL_Color color, int size)
{
    auto font = graphics->getFont("../content/unifont-8.0.01.ttf", size);
//	auto font = graphics->getFont("../content/Junicode.ttf", size);
	if (font == nullptr)
	{
		auto error = TTF_GetError();
		throw std::runtime_error(std::string("Failed to load font: ") + error);
	}

	SDL_Surface *surf = get_surface(font, message, color, SDL_Color{ 0, 0, 0 });

		return generate_texture(graphics, surf);
}

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, std::string message, SDL_Color color, int size)
{
    auto font = graphics->getFont("../content/unifont-8.0.01.ttf", size);
//	auto font = graphics->getFont("../content/Junicode.ttf", size);
	if (font == nullptr)
	{
		auto error = TTF_GetError();
		throw std::runtime_error(std::string("Failed to load font: ") + error);
	}

    auto surf = get_surface(font, message, color, SDL_Color{0, 0, 0 });

	return generate_texture(graphics, surf);
}

SDL_Texture *FontSprite::generate_texture(Graphics *graphics, SDL_Surface *surf)
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

void FontSprite::draw(int x, int y, int offsetX, int offsetY, int alpha)
{
	auto size = Renderer::TILE_SIZE;
	auto midSourceX = _source_rect.w / 2.0;
	auto midSourceY = _source_rect.h / 2.0;
	auto newOffsetX = size / 2.0 - midSourceX;
	auto newOffsetY = size / 2.0 - midSourceY;
	Sprite::draw(x, y, offsetX-newOffsetX, offsetY-newOffsetY,_source_rect.w, _source_rect.h, alpha);
//    Sprite::draw(x, y, offsetX, offsetY, _source_rect.w, _source_rect.h, alpha);

}
