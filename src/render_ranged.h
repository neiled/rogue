#ifndef RENDER_RANGED_H
#define RENDER_RANGED_H 

class Graphics;
class Renderer;
class Player;
class Tile;

class RenderRanged
{
public:
  RenderRanged (Graphics*);
  virtual ~RenderRanged ();

  void init();
  void render(Renderer&, Player&);

private:
  Graphics* _graphics;
  void draw_line(Renderer&, Tile&, Tile&);
};
#endif
