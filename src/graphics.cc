#include "graphics.h"
#include <SDL2_ttf/SDL_ttf.h>
#include <iostream>

Graphics::Graphics() {
}

Graphics::~Graphics()
{
  SDL_DestroyWindow(_window);
}

void Graphics::init()
{
  initTTF();
  _window = SDL_CreateWindow("YARL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Graphics::RES_W, Graphics::RES_H, SDL_WINDOW_OPENGL);
  Renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0x00 );
}

void Graphics::initTTF()
{
  if (TTF_Init() == -1)
  {
    std::cout << TTF_GetError() << std::endl;
  }
}


void Graphics::render()
{
  SDL_RenderPresent(Renderer);
}

void Graphics::clearScreen()
{
  SDL_RenderClear(Renderer);
}

int Graphics::getScreenWidth()
{
  return Graphics::RES_W;
}

int Graphics::getScreenHeight()
{
  return Graphics::RES_H;
}

SDL_Window* Graphics::window()
{
  return _window;
}

SDL_Texture* Graphics::loadTexture( std::string path )
{
  //The final texture
  SDL_Texture* newTexture = nullptr;

  //SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  SDL_Surface* loadedSurface = IMG_Load(path.c_str() );
  if(!loadedSurface)
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
  }
  else
  {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface );
    if(!newTexture)
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return newTexture;
}

SDL_Texture* Graphics::renderText(std::string message, std::string fontFile, 
                        SDL_Color color, int fontSize)
{
    //Open the font
    TTF_Font *font = nullptr;
    font = TTF_OpenFont(fontFile.c_str(), fontSize);
    if (font == nullptr)
        throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());
  
    //Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
    SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, surf);
    //Clean up unneeded stuff
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
 
    return texture;
}
