#include "sprite.h"

Sprite::Sprite(Graphics* graphics, SDL_Texture* texture, int source_x, int source_y, int width, int height)
{
  _graphics = graphics;
  _texture = texture;//_graphics->loadTexture(file_path);on
  _source_rect.x = source_x;
  _source_rect.y = source_y;
  _source_rect.w = width;
  _source_rect.h = height;
}

Sprite::~Sprite()
{
  SDL_DestroyTexture(_texture);
}

void Sprite::draw(int x, int y, int offsetX, int offsetY, int alpha)
{
    draw(x, y, offsetX, offsetY,_source_rect.w, _source_rect.h, alpha);
}
void Sprite::draw(int x, int y, int offsetX, int offsetY, int width, int height, int alpha)
{
    draw(x, y, offsetX, offsetY, width, height, alpha, 1.0);

}


void Sprite::draw(int x, int y, int offsetX, int offsetY, int width, int height, int alpha, double zoom)
{
    SDL_Rect destination;
    destination.x = x - offsetX;
    destination.y = y - offsetY;
    destination.w = width;
    destination.h = height;

    SDL_Rect source;
    source.x = _source_rect.x;// + offsetX;
    source.y = _source_rect.y;// + offsetY;
    source.w = (int) (width / zoom);
    source.h = (int) (height / zoom);

    SDL_SetTextureBlendMode(_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(_texture, alpha);
    SDL_RenderCopy(_graphics->Renderer, _texture, &source, &destination);
}
