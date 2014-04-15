#ifndef RENDER_RANGED_H
#define RENDER_RANGED_H 

class Graphics;
class Renderer;
class Player;

class RenderRanged
{
public:
  RenderRanged (Graphics*);
  virtual ~RenderRanged ();

  void init();
  void render(Renderer&, Player&);

private:
  Graphics* _graphics;
};
#endif
