#ifndef GRAPHICS_H_
#define GRAPHICS_H_ 

#include "stdio.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>


class Graphics
{
  public:
      Graphics ();
    virtual ~Graphics ();
    SDL_Renderer* Renderer;

    SDL_Texture* loadTexture( std::string path );
    void render();
    void clearScreen();
    int getScreenWidth();
    int getScreenHeight();

  private:
    SDL_Window* _window;
};

#endif
