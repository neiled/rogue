#ifndef RENDERER_H_
#define RENDERER_H_


#include <vector>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>

using std::vector;

class Player;
class Sprite;
class DirectionalSprite;
class World;
class Graphics;
class Level;

class Renderer {
  public:
    Renderer(Graphics* graphics);
    ~Renderer();
  
    void render(Level* level);
    void render(Player* player);
    void update(World* world, int elapsed_time_in_ms);

    const static int TILE_WIDTH = 32;
    const static int TILE_HEIGHT = 32;
    
  private:
    //vector<Sprite*> _mapTiles;
    //array<Sprite*, 5> _mapTiles;
    Sprite* _mapTiles[5];
    DirectionalSprite* _player;
    Graphics* _graphics;

    void updateCamera(Player* player);
    
    SDL_Rect _cameraRect;
    


};
#endif
