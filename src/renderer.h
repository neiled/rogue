#ifndef RENDERER_H_
#define RENDERER_H_

#include <boost/scoped_ptr.hpp>
#include "sprite.h"

class Renderer {
  public:
    Renderer();
    ~Renderer();
  
    void render(Level* level);
    
  private:


};
#endif
