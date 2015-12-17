//
// Created by Neil Edwards on 12/16/15.
//

#include <vector>
#include "FontSprite.h"

SDL_Texture *FontSprite::generate_texture(Graphics* graphics, std::string message, SDL_Color color, int size)
{
    TTF_Font *font = graphics->getFont("./content/unifont-8.0.01.ttf", 16);
    if (font == nullptr)
        throw std::runtime_error(std::string("Failed to load font: ") + TTF_GetError());

    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderUNICODE_Shaded(font, std::string("�"), color, SDL_Color{0,0,0});
//    SDL_Surface *surf = TTF_RenderUNICODE_Shaded(font, message.c_str(), color, SDL_Color{0,0,0});
    SDL_Texture *texture = SDL_CreateTextureFromSurface(graphics->Renderer, surf);
    SDL_Texture *t = SDL_CreateTexture(graphics->Renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET, size, size);

    int iW, iH;
    SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
    int x = size / 2 - iW / 2;
    int y = size / 2 - iH / 2;

    auto current_target = SDL_GetRenderTarget(graphics->Renderer);

    SDL_SetRenderTarget(graphics->Renderer, t);
    graphics->renderTexture(texture, x, y);

    SDL_SetRenderTarget(graphics->Renderer, current_target);

    //Clean up unneeded stuff
    SDL_FreeSurface(surf);

    return texture;
}
