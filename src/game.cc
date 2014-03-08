#include "game.h"
#include "world.h"
#include "actor.h"
#include "player.h"
#include "messages.h"
#include "item_factory.h"
#include "command_decoder_game.h"
#include "command_decoder_inventory.h"
#include "command_decoder_dead.h"


Game::Game() : _graphics(), _renderer(&_graphics)
{
}

Game::~Game() {
  SDL_Quit();
}

void Game::start()
{
  SDL_Init(SDL_INIT_EVERYTHING);
  _graphics.init();
  _renderer.init();
  //_renderer = Renderer(&_graphics);
  ItemFactory::Init();
  _world.init();
  _decoders[GameState::GAME] = new CommandDecoderGame();
  _decoders[GameState::MENU_INVENTORY] = new CommandDecoderInventory();
  _decoders[GameState::DEAD] = new CommandDecoderDead();
  _state = GameState::GAME;
  eventLoop();
}

void Game::reset()
{
  _turn = 0;
  _world = World();
  _world.init();
  Messages::Clear();
  _state = GameState::GAME;
  end_turn();
}

void Game::eventLoop()
{
  SDL_Log("Creating Graphics");
  //Graphics graphics;
  SDL_Event event;
  SDL_Log("Creating renderer");
  //Renderer renderer(&graphics);
  SDL_Log("Done renderer");
  CommandProcessor cProc;
  end_turn();
  player()->add_seen_items();
  //int last_update_time = SDL_GetTicks();


  bool running = true;
  while (running == true)
  {
    Player* player = _world.player();
    //const int start_time_ms = SDL_GetTicks();
    draw(_graphics, _renderer);
    SDL_WaitEvent(&event);

    decode_event(event, _graphics, _renderer);

    if(_state == GameState::GAME && player->dead())
      _state = GameState::DEAD;
    else
    {
      while(player->hasCommands())
      {
        if(cProc.Process(player->popCommand(), *player))
        {
          end_turn();
          draw(_graphics, _renderer);
        }
      }
    }


    //int current_time = SDL_GetTicks();
    //updateGraphics(&renderer);
    //last_update_time = current_time;

    //delay(start_time_ms);

    if(_state == GameState::STARTING)
    {
      reset();
    }
    if(_state == GameState::STOP)
      running = false;

  }

}


void Game::end_turn()
{
  ++_turn;
  _world.update();
  Messages::Push();
}

int Game::turn()
{
  return _turn;
}

void Game::decode_event(SDL_Event& event, Graphics& graphics, Renderer& renderer)
{
  switch(event.type)
  {
    case SDL_KEYDOWN:
    {
      auto decoded = _decoders[_state]->Decode(event.key.keysym.sym, *this);
      if(decoded)
      {
        player()->add_seen_items();
        draw(graphics, renderer);
      }
      break;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      auto decoded = _decoders[_state]->Decode(event.button.button, 1, event.button.x, event.button.y, *this);

    }
    default:
      break;
  }
}

Tile* Game::get_tile_from_click(int x, int y)
{
  return _renderer.get_tile_from_coord(*level(), x, y);
}

void Game::state(GameState state)
{
  _state = state;
}

GameState Game::state()
{
  return _state;
}

Player* Game::player()
{
  return _world.player();
}


Level* Game::level()
{
  return &_world.getCurrentLevel();
}

void Game::delay(int start_time_ms)
{
  const int elapsed_time_ms = SDL_GetTicks() - start_time_ms;
  int timeToDelay = 1000 / 30 - elapsed_time_ms;
  timeToDelay = timeToDelay < 0 ? 0 : timeToDelay;

  SDL_Delay(timeToDelay);  
}

void Game::draw(Graphics& graphics, Renderer& renderer)
{
  renderer.update(&_world);
  graphics.clearScreen();
  renderer.render(*this);
  graphics.render();
}
   
