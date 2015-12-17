#include "directional_sprite.h"
#include "renderer.h"

DirectionalSprite::DirectionalSprite(Graphics* graphics, SDL_Texture* texture, int source_x, int source_y,
                                     int width, int height) : Sprite(graphics, texture, source_x, source_y, width, height)
{
}

DirectionalSprite::~DirectionalSprite()
{
}

void DirectionalSprite::update(Actor::Direction direction)
{
  _source_rect.x = ((int)direction) * Renderer::TILE_SIZE;
}
