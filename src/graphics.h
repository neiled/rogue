#ifndef GRAPHICS_H_
#define GRAPHICS_H_ 

#include "stdio.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <map>



class Graphics
{
  public:
    Graphics ();
    virtual ~Graphics ();
    void init();
    SDL_Renderer* Renderer;

    SDL_Texture* loadTexture( std::string path );
    SDL_Texture* renderText(std::string message, std::string fontFile, SDL_Color color, int fontSize);
    void render();
    void clearScreen();
    int getScreenWidth();
    int getScreenHeight();
    SDL_Window* window();

    static const int RES_W = 1600;
    static const int RES_H = 900;

  private:
    SDL_Window* _window;

    void initTTF();

    std::map<std::string, TTF_Font*> _fonts;
};

#endif
