#ifndef GAME_H_
#define GAME_H_

#include <map>
#include "world.h"

class Renderer;
class Graphics;
class CommandDecoder;

class Game {
  public:
    Game();
    ~Game();

    enum class GameState {GAME, MENU_INVENTORY, STOPPED};

    void state(GameState state);
    Player* player();

  private:
    void eventLoop();
    void update();
    void updateGraphics(Renderer* renderer,  int elapsed_time_ms);
    void draw(Graphics* graphics, Renderer* renderer);

    void delay(int start_time_ms);

    int _turn;

    GameState _state;

    std::map<Game::GameState, CommandDecoder*> _decoders;
    World _world;

};
#endif
