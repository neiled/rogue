#include "game.h"
#include "world.h"
#include "actor.h"
#include "player.h"
#include "messages.h"
#include "item_factory.h"
#include "command_decoder_game.h"
#include "command_decoder_inventory.h"
#include "command_decoder_dead.h"
#include "command_decoder_chest.h"
#include "command_decoder_look.h"


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
  _decoders[GameState::MENU_WAND] = new CommandDecoderWand();
  _decoders[GameState::MENU_CHEST] = new CommandDecoderChest();
  _decoders[GameState::DEAD] = new CommandDecoderDead();
  _decoders[GameState::LOOK] = new CommandDecoderLook();
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
  CommandProcessor cProc;

  end_turn();
  player()->add_seen_items();
  draw(_graphics, _renderer);


  Player* player = _world.player();
  bool running = true;
  while (running == true)
  {
    if(_state == GameState::GAME && player->dead())
      _state = GameState::DEAD;

    player->start_turn();

    do
    {
      if(player->hasCommands() == false)
      {
        //SDL_Log("%d points left, Waiting for a valid event.", player->action_points());
        SDL_Event event;
        do
        {
          SDL_WaitEvent(&event);
        }while(!decode_event(event, _graphics, _renderer));
        draw(_graphics, _renderer);
      }

      while(!player->dead() && player->can_afford_next_command())
      {
        cProc.Process(player->popCommand(), *player);
        draw(_graphics, _renderer);
        //SDL_Log("%d points left.", player->action_points());
      }
    } while(player_can_continue(*player, _state));
    player->end_turn();
    end_turn();

    if(_state == GameState::STARTING)
    {
      reset();
    }
    if(_state == GameState::STOP)
      running = false;

  }

}

bool Game::player_can_continue(Player& player, GameState state)
{
  if(player.dead())
    return false;
  if(_state == GameState::STOP)
    return false;
  if(_state == GameState::STARTING)
    return false;
  if(player.action_points() <= 0)
    return false;
  if(player.hasCommands())
    return false;

  return true;
}


void Game::end_turn()
{
  ++_turn;
  _world.update();
  update_monsters();
  Messages::Push();
  draw(_graphics, _renderer);
}

void Game::update_monsters()
{
  //SDL_Log("Staring monsters turn...");
  CommandProcessor cProc;
  for(auto m : level()->monsters())
  {
    //SDL_Log("New Monster starts turn");
    m->start_turn();
    do
    {
      //SDL_Log("Started turn");
      if(m->hasCommands() == false)
      {
        //SDL_Log("Thinking");
        m->think();
      }
      while(!m->dead() && m->can_afford_next_command())
      {
        //SDL_Log("Peforming monster commands.");
        cProc.Process(m->popCommand(), *m);
        //draw(_graphics, _renderer);
      }
    }while(m->action_points() > 0 && m->hasCommands() == false);

    //SDL_Log("Ending turn of monster");
    m->end_turn();      
  }
}


int Game::turn()
{
  return _turn;
}

bool Game::decode_event(SDL_Event& event, Graphics& graphics, Renderer& renderer)
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
      return decoded;
    }
    case SDL_MOUSEBUTTONDOWN:
    {
      auto decoded = _decoders[_state]->Decode(event.button.button, 1, event.button.x, event.button.y, *this);
      if(decoded)
      {
        draw(graphics, renderer);
      }
      return decoded;
    }
    default:
      return false;
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
  return _world.current_level();
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
   
