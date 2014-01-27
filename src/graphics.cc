#include "graphics.h"

Graphics::Graphics() {
  _window = SDL_CreateWindow("My Game Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
  Renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
  SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

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
//void Graphics::blitSurface(SDL_Surface* source, SDL_Rect* source_rect, SDL_Rect* dest_rect)
//{
  //SDL_BlitSurface(source, source_rect, _screen, dest_rect);
//}

//SDL_Surface* Graphics::loadSurface(std::string path)
//{
  //SDL_Surface* optimisedSurface = NULL;

  //SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  //if(loadedSurface == NULL)
    //fprintf(stderr, "Unable to load the image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
  //else
  //{
    //optimisedSurface = SDL_ConvertSurface(loadedSurface, _surfaceWindow->format, NULL);
    //SDL_FreeSurface(loadedSurface);
  //}
  //return optimisedSurface;
//}

SDL_Texture* Graphics::loadTexture( std::string path )
{
  //The final texture
  SDL_Texture* newTexture = NULL;

  //SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
  SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
  if( loadedSurface == NULL )
  {
    printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), SDL_GetError() );
  }
  else
  {
    //Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface(Renderer, loadedSurface );
    if( newTexture == NULL )
    {
      printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );
  }

  return newTexture;
}
