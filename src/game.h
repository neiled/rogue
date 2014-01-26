#ifndef GAME_H_
#define GAME_H_



struct Game {
  Game();
  ~Game();

  private:
    void eventLoop();
    void update();
    void draw();

};
#endif
