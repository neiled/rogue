#include "directional_sprite.h"
#include "renderer.h"

DirectionalSprite::DirectionalSprite(Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height) : Sprite(graphics, file_path, source_x, source_y, width, height)
{
}

DirectionalSprite::~DirectionalSprite()
{
}

void DirectionalSprite::update(Actor::Direction direction)
{
  _source_rect.x = ((int)direction) * Renderer::TILE_SIZE;
}
