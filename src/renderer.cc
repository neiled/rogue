#include "renderer.h"
#include "tile.h"
#include "sprite.h"
#include "directional_sprite.h"
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "monster.h"
#include "world.h"
#include "item.h"
#include "game.h"
#include "messages.h"
#include "render_monsters.h"

Renderer::Renderer(Graphics* graphics) : _render_inv(graphics)
{
  _graphics = graphics;
  loadMapTiles();
  loadMonsterTiles();
  load_items();
  load_info();

  _player = new DirectionalSprite(_graphics, "../content/player.png", 0, 0, TILE_SIZE, TILE_SIZE);


  init_viewports();

}

Renderer::~Renderer()
{

}

void Renderer::render(Game& game)
{
  render(*game.level());
  render(*game.player());
  render_info(*game.player());
  render_messages(Messages::AllMessages());
  render_state(game.state(), *game.player());
  
}


void Renderer::init_viewports()
{
  int screen_h = _graphics->getScreenHeight();
  int screen_w = _graphics->getScreenWidth();
  SDL_Log("Screen h:%d, w:%d", screen_h, screen_w);

  int msg_h = 200;
  int info_w = 224;

  _vp_main.w = screen_w-info_w;
  _vp_main.h = screen_h-msg_h;
  _vp_main.x = 0;
  _vp_main.y = msg_h;

  _vp_info.w = screen_w - _vp_main.w;
  _vp_info.h = screen_h;
  _vp_info.x = screen_w - _vp_info.w;//_vp_main.x + _vp_main.w;
  _vp_info.y = 0;//screen_h;

  _vp_msg.h = msg_h;
  _vp_msg.w = screen_w - _vp_info.w;
  _vp_msg.x = 0;
  _vp_msg.y = 0;//screen_h - _vp_main.h;

  _cameraRect.w= _vp_main.w;
  _cameraRect.h= _vp_main.h;
  _cameraRect.x = 0;
  _cameraRect.y = 0;
}

void Renderer::loadMonsterTiles()
{
  _monsters[Monster::MonsterType::Orc] = new DirectionalSprite(_graphics, "../content/monsters/monster_orc.png", 0, 0, TILE_SIZE, TILE_SIZE);
}

void Renderer::loadMapTiles()
{
  _mapTiles[(int)Tile::TileType::Floor] =  new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, TILE_SIZE, TILE_SIZE);

  _mapTiles[(int)Tile::TileType::StairsUp] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_SIZE, 2*TILE_SIZE, TILE_SIZE, TILE_SIZE);

  _mapTiles[(int)Tile::TileType::StairsDown] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 11*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE);

  _mapTiles[(int)Tile::TileType::Rock] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE);

  _mapTiles[(int)Tile::TileType::Door] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 13*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void Renderer::load_items()
{
  load_corpses();
  load_potions();
  load_weapons();
}

void Renderer::load_corpses()
{
  _items[Item::ItemType::CORPSE] = std::map<Item::ItemSubtype, Sprite*>();
  _items[Item::ItemType::CORPSE][Item::ItemSubtype::CORPSE_ORC] = new Sprite(_graphics, "../content/corpse.png", 0, 0, TILE_SIZE, TILE_SIZE);


}

void Renderer::load_potions()
{
  _items[Item::ItemType::POTION] = std::map<Item::ItemSubtype, Sprite*>();
  _items[Item::ItemType::POTION][Item::ItemSubtype::POTION_HEALTH] = new Sprite(_graphics, "content/potion.png", 0, 0, TILE_SIZE, TILE_SIZE); 
}

void Renderer::load_weapons()
{
  _items[Item::ItemType::WEAPON] = std::map<Item::ItemSubtype, Sprite*>();
  _items[Item::ItemType::WEAPON][Item::ItemSubtype::WEAPON_KRIS] = new Sprite(_graphics, "content/weapon.png", 0, 0, TILE_SIZE, TILE_SIZE); 
}

void Renderer::load_info()
{
  _info_char = new Sprite(_graphics, "../content/outline.png", 0, 0, 150, 271);
}

void Renderer::update(World* world)
{
  auto &player = *world->player();
  updateCamera(player);
}

void Renderer::updateCamera(Player& player)
{
  _cameraRect.x = player.tile()->x() * TILE_SIZE  - (_cameraRect.w/2);
  _cameraRect.y = player.tile()->y() * TILE_SIZE - (_cameraRect.h/2);

  
  if(_cameraRect.x < 0) _cameraRect.x = 0;
  if(_cameraRect.y < 0) _cameraRect.y = 0;
  if(_cameraRect.x >= Level::LEVEL_WIDTH*TILE_SIZE   - _cameraRect.w) _cameraRect.x = Level::LEVEL_WIDTH* TILE_SIZE  - _cameraRect.w;
  if(_cameraRect.y >= Level::LEVEL_HEIGHT*TILE_SIZE - _cameraRect.h) _cameraRect.y = Level::LEVEL_HEIGHT*TILE_SIZE - _cameraRect.h;
}



void Renderer::render(Level& level)
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_main);
  render_level(level);
  render_monsters(level);
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
}

void Renderer::render_monsters(Level& level)
{
  RenderMonsters::Render(*this, _monsters, level);
}

void Renderer::render_items(Tile& tile, int alpha)
{
  for(Item* item : tile.items())
  {
    _items[item->item_type()][item->item_subtype()]->draw(tile.x()*TILE_SIZE, tile.y()*TILE_SIZE, _cameraRect.x, _cameraRect.y, alpha);
  }

}

void Renderer::render_level(Level& level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Level::LightType lit = level.light_map(x, y);
      if(lit == Level::LightType::Unseen)
        continue;
      if(y*TILE_SIZE < _cameraRect.y)
        continue;
      if(y*TILE_SIZE > _cameraRect.y + _cameraRect.h)
        continue;
      if(x*TILE_SIZE > _cameraRect.x + _cameraRect.w)
        continue;
      if(x*TILE_SIZE < _cameraRect.x)
        continue;

      auto currentTile = level.tile(x, y);
      auto tileType = (int)currentTile->tile_type();
      int alpha = 255;

      if(lit == Level::LightType::Unlit)
        alpha = 100;
      else
      {
        auto intensity = level.light_intensity(x,y);
        alpha = static_cast<int>(255.0f * intensity);
        if(alpha < 128) alpha = 128;
      }

      _mapTiles[tileType]->draw(x*TILE_SIZE,y*TILE_SIZE, _cameraRect.x, _cameraRect.y, alpha);
      if(lit == Level::LightType::Lit)
        render_items(*currentTile, alpha);
    }
  }
}


void Renderer::render(Player& player)
{
  auto currentTile = player.tile();
  _player->update(player.direction);
  draw_sprite(_player, *currentTile);
}

void Renderer::draw_health(Actor& actor)
{
  if(actor.health() == actor.max_health())
    return;

  int x = actor.x()*TILE_SIZE - _cameraRect.x;
  int y = actor.y()*TILE_SIZE - _cameraRect.y + (TILE_SIZE-10);
  int w = TILE_SIZE;
  int h = 5;

  draw_health_bar(x, y, w, h, actor.health(), actor.max_health());
}

void Renderer::render_info(Player& player)
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_info);
  _info_char->draw(0, 0, 0, 0);
  if(player.weapon())
  {
    auto item = _items[player.weapon()->item_type()][player.weapon()->item_subtype()];
    item->draw(140, 125, 0, 0, SDL_ALPHA_OPAQUE);
    render_string("Wpn: " + player.weapon()->name() + " : " + std::to_string(player.weapon()->max_damage()), 0, 450, 16);
  }
  draw_health_bar(0, 300, 150, 20, player.health(), player.max_health());

  draw_health_bar(0, 330, 150, 20, player.xp() - player.min_xp(), player.max_xp());

  render_string("Lvl: " + std::to_string(player.xp_level()), 0, 360, 16);
  render_string("Atk: " + std::to_string(player.atk()), 0, 390, 16);
  render_string("Def: " + std::to_string(player.def()), 0, 420, 16);

}

void Renderer::draw_health_bar(int x, int y, int width, int height, int current_health, int max_health)
{
  SDL_Rect health;
  health.x = x;
  health.y = y;
  health.w = width;
  health.h = height;
  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawRect(_graphics->Renderer, &health);

  health.x++;
  health.y++;
  health.h-=2;
  health.w = (width-2) * (static_cast<float>(current_health) / max_health);
  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(_graphics->Renderer, &health);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Renderer::render_messages(std::deque<std::string> messages)
{
  if(messages.empty())
    return;
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_msg);

  int message_h = 16;
  int max_messages = _vp_msg.h / message_h;
  int start_message = messages.size()-max_messages;
  if(start_message < 0)
    start_message = 0;

  int current = 0;
  for (int i = start_message; i < messages.size() && current <= max_messages; ++i)
  {
    std::string message = messages.at(i);
    render_string(message, 25, current++*message_h, message_h);
  }
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
}

void Renderer::render_string(std::string message, int x, int y, int h)
{
    auto messageT = render_message(message, h);
    SDL_Rect dst;
    dst.x = x;
    dst.y = y;
    SDL_QueryTexture(messageT, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(_graphics->Renderer, messageT, NULL, &dst);
    SDL_DestroyTexture(messageT);
}

void Renderer::render_state(Game::GameState state, Player& player)
{
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
  switch(state)
  {
    case Game::GameState::MENU_INVENTORY:
      render_inventory(*player.inventory());
      break;
    default:
      break;
  }

}

void Renderer::render_inventory(Inventory& inventory)
{
  _render_inv.render(*this, _items, inventory);
}

SDL_Texture* Renderer::render_message(std::string message, int height)
{
  return _graphics->renderText(message, "../content/secrcode.ttf", SDL_Color {255,255,255}, height);
}

void Renderer::draw_sprite(Sprite* sprite, Tile& tile)
{
  sprite->draw(tile.x()*TILE_SIZE, tile.y()*TILE_SIZE, _cameraRect.x, _cameraRect.y);

}
