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
#include "chest.h"

Renderer::Renderer(Graphics* graphics) : _graphics(graphics), _render_inv(graphics), _render_level(graphics), _render_info(graphics), _render_ranged(graphics), _render_look(graphics)
{

}

Renderer::~Renderer()
{

}

void Renderer::init()
{
  loadMapTiles();
  loadMonsterTiles();
  load_items();

  _player = new DirectionalSprite(_graphics, "./content/player.png", 0, 0, TILE_SIZE, TILE_SIZE);


  init_viewports();

  _render_inv.init();
  _render_info.init();
  _render_ranged.init();
}

SDL_Rect Renderer::camera_rect()
{
  return _cameraRect;
}

void Renderer::render(Game& game)
{
  render(*game.level());
  render(*game.player());
  render_info(game, *game.player());
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
  _monsters[MonsterType::Orc] = new DirectionalSprite(_graphics, "./content/monsters/monster_orc.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _monsters[MonsterType::Devil] = new DirectionalSprite(_graphics, "./content/monsters/monster_devil.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _monsters[MonsterType::Skeleton] = new DirectionalSprite(_graphics, "./content/monsters/monster_skeleton.png", 0, 0, TILE_SIZE, TILE_SIZE);
}

void Renderer::loadMapTiles()
{
  for (int i = 0; i < 7; ++i)
  {
    _tiles[TileType::Floor].push_back(new Sprite(_graphics, "./content/dungeon_tiles_32.png", i*TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

  }

  for (int i = 0; i < 4; ++i)
  {
    _tiles[TileType::Rock].push_back(new Sprite(_graphics, "./content/dungeon_tiles_32.png", i*TILE_SIZE, 1*TILE_SIZE, TILE_SIZE, TILE_SIZE));
  }

  _tiles[TileType::StairsUp].push_back(new Sprite(_graphics, "./content/dungeon_tiles_32.png", 12*TILE_SIZE, 2*TILE_SIZE, TILE_SIZE, TILE_SIZE));

  _tiles[TileType::StairsDown].push_back(new Sprite(_graphics, "./content/dungeon_tiles_32.png", 11*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE));

  _tiles[TileType::Door].push_back(new Sprite(_graphics, "./content/dungeon_tiles_32.png", 13*TILE_SIZE, 5*TILE_SIZE, TILE_SIZE, TILE_SIZE));
}

void Renderer::load_items()
{
  load_corpses();
  load_potions();
  load_weapons();
  load_wands();
  load_scrolls();
  load_scenery();
}

void Renderer::load_scenery()
{
  _items[ItemType::CHEST] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::CHEST][ItemSubtype::CHEST] = new Sprite(_graphics, "./content/chest.png", 0, 0, TILE_SIZE, TILE_SIZE);

}

void Renderer::load_corpses()
{
  _items[ItemType::CORPSE] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::CORPSE][ItemSubtype::CORPSE_ORC] = new Sprite(_graphics, "./content/corpse.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::CORPSE][ItemSubtype::CORPSE_DEVIL] = new Sprite(_graphics, "./content/corpse.png", TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::CORPSE][ItemSubtype::CORPSE_SKELETON] = new Sprite(_graphics, "./content/corpse.png", TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);


}

void Renderer::load_potions()
{
  _items[ItemType::POTION] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::POTION][ItemSubtype::POTION_HEALTH_LARGE] = new Sprite(_graphics, "content/potion.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::POTION][ItemSubtype::POTION_HEALTH] = new Sprite(_graphics, "content/potion.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::POTION][ItemSubtype::POTION_HEALTH_SMALL] = new Sprite(_graphics, "content/potion.png", TILE_SIZE, 0, TILE_SIZE, TILE_SIZE);
}

void Renderer::load_weapons()
{
  _items[ItemType::WEAPON] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::WEAPON][ItemSubtype::WEAPON_KRIS_LOW] = new Sprite(_graphics, "content/weapon.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::WEAPON][ItemSubtype::WEAPON_KRIS] = new Sprite(_graphics, "content/weapon.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::WEAPON][ItemSubtype::WEAPON_KRIS_RUSTED] = new Sprite(_graphics, "content/weapon.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::WEAPON][ItemSubtype::WEAPON_KRIS_GOOD] = new Sprite(_graphics, "content/weapon.png", 0, 0, TILE_SIZE, TILE_SIZE);
}

void Renderer::load_wands()
{
  _items[ItemType::WAND] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::WAND][ItemSubtype::WAND_FLAME] = new Sprite(_graphics, "content/wand.png", 0, 0, TILE_SIZE, TILE_SIZE);
}

void Renderer::load_scrolls()
{
  _items[ItemType::SCROLL] = std::map<ItemSubtype, Sprite*>();
  _items[ItemType::SCROLL][ItemSubtype::SCROLL_BLINK] = new Sprite(_graphics, "content/scroll.png", 0, 0, TILE_SIZE, TILE_SIZE);
  _items[ItemType::SCROLL][ItemSubtype::SCROLL_REVEAL] = new Sprite(_graphics, "content/scroll.png", 0, 0, TILE_SIZE, TILE_SIZE);
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


void Renderer::render_level(Level& level)
{
  _render_level.render(*this, _cameraRect, _tiles, _items, level);
}

Tile* Renderer::get_tile_from_coord(Level& level, int x, int y)
{
  if(x > _cameraRect.w)
    return nullptr;
  if(y > _cameraRect.h)
    return nullptr;
  int final_x = x + _cameraRect.x;
  int final_y = y + _cameraRect.y;
  final_x /= TILE_SIZE;
  final_y /= TILE_SIZE;

  auto tile = level.tile(final_x, final_y);
  auto lit = level.light_map(final_x, final_y);
  if(lit == Level::LightType::Unseen)
    return nullptr;

  return tile;

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

  draw_health_bar(x, y, w, h, actor.health(), actor.max_health(), actor.previous_health());
}

void Renderer::render_info(Game& game, Player& player)
{
  _render_info.render(*this, game, _items, _vp_info);
}

void Renderer::draw_bar(int x, int y, int width, int height, int current, int max, int r, int g, int b, bool background)
{
  SDL_Rect health;
  health.x = x;
  health.y = y;
  health.w = width;
  health.h = height;

  if(background)
  {
    SDL_SetRenderDrawColor(_graphics->Renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(_graphics->Renderer, &health);
  }

  health.x++;
  health.y++;
  health.h-=2;
  health.w = (width-2) * (static_cast<float>(current) / max);

  SDL_SetRenderDrawColor(_graphics->Renderer, r, g, b, SDL_ALPHA_OPAQUE);
  SDL_RenderFillRect(_graphics->Renderer, &health);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Renderer::draw_xp_bar(int x, int y, int width, int height, int current, int max)
{
  draw_bar(x, y, width, height, current, max, 81, 95, 240);
}

void Renderer::draw_health_bar(int x, int y, int width, int height, int current_health, int max_health, int previous_health)
{
  int r,g,b;
  float current_percent = (static_cast<float>(current_health) / max_health);
  if(current_percent < 0.25)
  {
    r = 255;
    g = 0;
    b = 0;
  }
  else if(current_percent < 0.5)
  {
    r = 255;
    g = 187;
    b = 0;
  }
  else
  {
    r = 0;
    g = 255;
    b = 0;
  }
  if(previous_health > current_health)
  {
    draw_bar(x, y, width, height, previous_health, max_health, 100, 0, 0);
    draw_bar(x, y, width, height, current_health, max_health, r, g, b, false);
  }
  else
  {
    draw_bar(x, y, width, height, current_health, max_health, r, g, b);
  }
}

void Renderer::render_messages(std::deque<std::vector<Message>> messages)
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
    auto current_messages = messages.at(i);
    render_message(current_messages, 25, current++ * message_h, message_h);

    //std::string message = messages.at(i);
    //render_string(message, 25, current++*message_h, message_h);
  }
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
}

void Renderer::render_message(std::vector<Message> messages, int x, int y, int h)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  for(auto message : messages)
  {
    auto current = render_message(message.message, h, calc_color(message.message_type));
    SDL_QueryTexture(current, NULL, NULL, &dst.w, &dst.h);
    SDL_RenderCopy(_graphics->Renderer, current, NULL, &dst);
    SDL_DestroyTexture(current);
    dst.x += dst.w;
  }
}

SDL_Color Renderer::calc_color(MessageType type)
{
  switch(type)
  {
    case MessageType::Normal:
      return SDL_Color{255,255,255};
    case MessageType::Good:
      return SDL_Color{0,255,0};
    case MessageType::Bad:
      return SDL_Color{255,0,0};
  }
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

void Renderer::render_state(GameState state, Player& player)
{
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
  switch(state)
  {
    case GameState::MENU_INVENTORY:
      render_inventory(*player.inventory());
      break;
    case GameState::MENU_WAND:
      render_wand(*player.inventory());
      break;
    case GameState::MENU_CHEST:
      render_chest(*player.chest()->inventory());
      break;
    case GameState::LOOK:
      render_look(player);
      break;
    case GameState::RANGED_TARGET:
      render_ranged(player);
    default:
      break;
  }

}

void Renderer::render_look(Player& player)
{
  _render_look.render(*this, player);
  //if(!player.level().look_tile())
    //return;

  //auto point = tile_to_screen(player.level().look_tile()->x(), player.level().look_tile()->y());
  //SDL_Rect look;
  //look.x = point.x;
  //look.y = point.y;
  //look.w = TILE_SIZE;
  //look.h = TILE_SIZE;

  //if(look.x > _cameraRect.x + _cameraRect.w-TILE_SIZE)
    //return;
  //if(look.y > _cameraRect.y + _cameraRect.h-TILE_SIZE)
    //return;


  //SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
  //SDL_RenderDrawRect(_graphics->Renderer, &look);
  //SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}


void Renderer::render_inventory(Inventory& inventory)
{
  _render_inv.render_player_inventory(*this, _items, inventory);
}

void Renderer::render_wand(Inventory& inventory)
{
  _render_inv.render_player_wands(*this, _items, inventory);
}

void Renderer::render_chest(Inventory& inventory)
{
  _render_inv.render_chest_inventory(*this, _items, inventory);
}

void Renderer::render_ranged(Player& player)
{
  _render_ranged.render(*this, player);
}

SDL_Texture* Renderer::render_message(std::string message, int height, SDL_Color color)
{
  return _graphics->renderText(message, "./content/secrcode.ttf", color, height);
}

void Renderer::draw_sprite(Sprite* sprite, Tile& tile)
{
  sprite->draw(tile.x()*TILE_SIZE, tile.y()*TILE_SIZE, _cameraRect.x, _cameraRect.y);

}

SDL_Point Renderer::tile_to_screen(int x, int y)
{
  SDL_Point p;
  p.x = x*TILE_SIZE-_cameraRect.x;
  p.y = y*TILE_SIZE-_cameraRect.y;

  return p;
}
