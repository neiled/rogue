#include "animated_sprite.h"
#include "renderer.h"

AnimatedSprite::AnimatedSprite(Graphics* graphics, const std::string& file_path,
      int source_x, int source_y, int width, int height, int fps, int num_frames) : Sprite(graphics, file_path, source_x, source_y, width, height), _frame_time(1000/fps), _num_frames(num_frames)
{
  _current_frame = 0;
  _elapsed_time = 0;
}

AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::update(int elapsed_time_in_ms)
{
  _elapsed_time += elapsed_time_in_ms;
  if (_elapsed_time > _frame_time)
  {
    ++_current_frame;
    _elapsed_time = 0;
    if (_current_frame < _num_frames)
      _source_rect.x += Renderer::TILE_WIDTH;
    else
    {
      _source_rect.x -= Renderer::TILE_WIDTH * (_num_frames - 1);
      _current_frame = 0;
    }
    
  }
}
