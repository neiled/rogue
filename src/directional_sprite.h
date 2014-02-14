#ifndef DIRECTIONAL_SPRITE_H
#define DIRECTIONAL_SPRITE_H 

#include "sprite.h"
#include "actor.h"

class DirectionalSprite : public Sprite
{
public:
  DirectionalSprite (Graphics* graphics, const std::string& file_path, int source_x, int source_y, int width, int height);
  virtual ~DirectionalSprite ();
  void update(Actor::Direction direction);

private:
  /* data */
};
#endif
