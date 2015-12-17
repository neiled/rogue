#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H 

#include "sprite.h"

class AnimatedSprite : public Sprite
{
public:
  AnimatedSprite(Graphics* graphics, const std::string& file_path,
      int source_x, int source_y, int width, int height, int fps, int num_frames);

    AnimatedSprite(Graphics *graphics, SDL_Texture *texture, int source_x, int source_y, int width, int height, int fps,
                       int num_frames);

    virtual ~AnimatedSprite ();
  void update(int elapsed_time_in_ms);

private:
  const int _frame_time;
  const int _num_frames;
  int _current_frame;
  int _elapsed_time;
  
};
#endif
