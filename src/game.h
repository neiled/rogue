#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <array>
#include "world.h"
#include "monster.h"
#include "item.h"
#include <SDL2/SDL.h>
#include "graphics.h"
#include "renderer.h"
#include "game_types.h"

class CommandDecoder;
class DirectionalSprite;
class Sprite;

class Game {
  public:
    Game();
    ~Game();

    void start();


    void state(GameState state);
    GameState state();
    Player* player();
    Level* level();
    World* world();
    int turn();

    Tile* get_tile_from_click(int x, int y);

  private:
    Graphics _graphics;
    Renderer _renderer;
    void start_game();
    void eventLoop();
    void update_monsters();
    void draw(Graphics& graphics, Renderer& renderer);
    void end_turn();

    void delay(int start_time_ms);
    bool decode_event(SDL_Event&, Graphics&, Renderer&);
    bool player_can_continue(Player& player, GameState state);

    int _turn;

    GameState _state;

    std::map<GameState, CommandDecoder*> _decoders;
    World _world;

};
#endif
