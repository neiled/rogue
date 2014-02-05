#ifndef GRAPHICS_H_
#define GRAPHICS_H_ 

#include <SDL2/SDL.h>
#include "stdio.h"
#include <string>

struct SDL_Surface;
struct SDL_Window;
struct SDL_Renderer;

class Graphics
{
  public:
      Graphics ();
    virtual ~Graphics ();
    SDL_Renderer* Renderer;

    //void blitSurface(SDL_Surface* source, SDL_Rect* source_rect, SDL_Rect* dest_rect);
    //SDL_Surface* loadSurface(std::string path);
    SDL_Texture* loadTexture( std::string path );
    void render();
    void clearScreen();
    int getScreenWidth();
    int getScreenHeight();

  private:
    SDL_Window* _window;
    SDL_Surface* _surfaceWindow;
};

#endif
