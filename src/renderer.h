#ifndef RENDERER_H_
#define RENDERER_H_


#include <vector>
#include "sprite.h"
#include "level.h"

using std::vector;

class Renderer {
  public:
    Renderer(Graphics* graphics);
    ~Renderer();
  
    void render(Level* level);
    
  private:
    vector<Sprite*> _mapTiles;
    Graphics* _graphics;
    


};
#endif
