#ifndef SPRITE_H_
#define SPRITE_H_ 

#include "graphics.h"

class Sprite
{
public:
    Sprite(Graphics *graphics, SDL_Texture *texture, int source_x, int source_y, int width, int height);

    virtual ~Sprite();

    virtual void draw(int x, int y, int offsetX, int offsetY, int alpha = 255);

    void draw(int x, int y, int offsetX, int offsetY, int width, int height, int alpha);

    void draw(int x, int y, int offsetX, int offsetY, int width, int height, int alpha, double zoom);
    //virtual void update(int elapsed_time_in_ms);

protected:
    SDL_Rect _source_rect;

private:
    SDL_Texture *_texture = nullptr;
    Graphics *_graphics = nullptr;

};

#endif
