#ifndef GAME_H_
#define GAME_H_

#include <map>
#include <array>
#include "world.h"
#include "monster.h"
#include "item.h"
#include <SDL2/SDL.h>

class Renderer;
class Graphics;
class CommandDecoder;
class DirectionalSprite;
class Sprite;



class Game {
  public:
    Game();
    ~Game();

    typedef std::map<Monster::MonsterType, DirectionalSprite*> monster_sprites_t;
    typedef std::map<Item::ItemType, std::map<Item::ItemSubtype, Sprite*>> item_sprites_t;
    enum class GameState {MENU_START, GAME, MENU_INVENTORY, DEAD, STARTING, STOP};

    void state(GameState state);
    GameState state();
    Player* player();
    Level* level();

  private:
    void reset();
    void eventLoop();
    //void update(Renderer& renderer);
    //void updateGraphics(Renderer* renderer,  int elapsed_time_ms);
    void draw(Graphics* graphics, Renderer* renderer);
    void end_turn();

    void delay(int start_time_ms);
    void decode_event(SDL_Event&, Graphics&, Renderer&);

    int _turn;

    GameState _state;

    std::map<Game::GameState, CommandDecoder*> _decoders;
    World _world;

};
#endif
