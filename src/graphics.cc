#include "graphics.h"

Graphics::Graphics() {
  _window = SDL_CreateWindow("My Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
  Renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  //SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
  SDL_SetRenderDrawColor( Renderer, 0x00, 0x00, 0x00, 0x00 );

}

Graphics::~Graphics()
{
  SDL_DestroyWindow(_window);
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
  return 800;
}

int Graphics::getScreenHeight()
{
  return 600;
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
