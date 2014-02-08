#include "sprite.h"

Sprite::Sprite(Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height)
{
  _graphics = graphics;
  _texture = _graphics->loadTexture(file_path);
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
  SDL_Rect destination;
  destination.x = x - offsetX;
  destination.y = y - offsetY;
  destination.w = _source_rect.w;
  destination.h = _source_rect.h;

  SDL_SetTextureAlphaMod(_texture, alpha);
  SDL_RenderCopy(_graphics->Renderer, _texture, &_source_rect, &destination);
}
