#ifndef RENDER_LOOK_H
#define RENDER_LOOK_H 

class Graphics;
class Player;
class Renderer;

class RenderLook
{
public:
  RenderLook (Graphics* g);
  virtual ~RenderLook ();
  void render(Renderer&, Player& player);

private:
  Graphics* _graphics;
};
#endif
