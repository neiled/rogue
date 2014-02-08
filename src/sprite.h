#ifndef SPRITE_H_
#define SPRITE_H_ 

#include "graphics.h"

class Sprite
{
  public:
  Sprite(Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height);
  virtual ~Sprite();
  void draw(int x, int y, int offsetX, int offsetY, int alpha = 255);
  virtual void update(int elapsed_time_in_ms) {}

  protected:
    SDL_Rect _source_rect;

  private:
    SDL_Texture* _texture;
    Graphics* _graphics;

};

#endif
