#ifndef GAME_H_
#define GAME_H_


class World;
class Renderer;
class Graphics;

struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update(World* world);
    void updateGraphics(World* world,Renderer* renderer,  int elapsed_time_ms);
    void draw(Graphics* graphics, Renderer* renderer, World* world);

    void delay(int start_time_ms);

    int _turn;

};
#endif
