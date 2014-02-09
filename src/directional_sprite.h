#ifndef DIRECTIONAL_SPRITE_H
#define DIRECTIONAL_SPRITE_H 

#include "world.h"
#include "sprite.h"

class DirectionalSprite : public Sprite
{
public:
  DirectionalSprite (Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height);
  virtual ~DirectionalSprite ();
  void update(World::Direction direction);

private:
  /* data */
};
#endif
