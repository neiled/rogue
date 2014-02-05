#ifndef RENDERER_H_
#define RENDERER_H_


#include <vector>
#include <array>
#include "sprite.h"
#include "world.h"
#include "level.h"
#include "player.h"

using std::vector;

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
    vector<Sprite*> _mapTiles;
    Sprite* _player;
    Graphics* _graphics;

    void updateCamera(Player* player);
    
    SDL_Rect _cameraRect;
    


};
#endif
