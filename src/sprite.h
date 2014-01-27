#ifndef SPRITE_H_
#define SPRITE_H_ 

#include "graphics.h"

class Sprite
{
  public:
  Sprite(Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height);
  ~Sprite();
  void draw(int x, int y);

  private:
    SDL_Texture* _texture;
    SDL_Rect _source_rect;
    Graphics* _graphics;

};

#endif
