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

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  loadMapTiles();
  loadMonsterTiles();
  load_items();

  _player = new DirectionalSprite(_graphics, "../content/player.png", 0, 0, TILE_WIDTH, TILE_HEIGHT);


  init_viewports();

}

Renderer::~Renderer()
{
}


void Renderer::init_viewports()
{
  int screen_h = _graphics->getScreenHeight();
  int screen_w = _graphics->getScreenWidth();
  SDL_Log("Screen h:%d, w:%d", screen_h, screen_w);

  _vp_main.w = 800;
  _vp_main.h = 668;
  _vp_main.x = 0;
  _vp_main.y = 100;

  _vp_info.w = screen_w - _vp_main.w;
  _vp_info.h = screen_h;
  _vp_info.x = screen_w - _vp_info.w;//_vp_main.x + _vp_main.w;
  _vp_info.y = 0;//screen_h;

  _vp_msg.h = 100;
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
  _monsters[(int)Monster::MonsterType::Orc] = new DirectionalSprite(_graphics, "../content/monsters/monster_orc.png", 0, 0, TILE_WIDTH, TILE_HEIGHT);
}

void Renderer::loadMapTiles()
{
  _mapTiles[(int)Tile::TileType::Floor] =  new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, TILE_WIDTH, TILE_HEIGHT);

  _mapTiles[(int)Tile::TileType::StairsUp] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_WIDTH, 2*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

  _mapTiles[(int)Tile::TileType::StairsDown] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 11*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

  _mapTiles[(int)Tile::TileType::Rock] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

  _mapTiles[(int)Tile::TileType::Door] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 13*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
}

void Renderer::load_items()
{
  _items[(int)Item::ItemType::ORC_CORPSE] = new Sprite(_graphics, "../content/items.png", 0, 0, TILE_WIDTH, TILE_HEIGHT);
}

void Renderer::update(World* world, int elapsed_time_in_ms)
{
  updateCamera(world->player());
}

void Renderer::updateCamera(Player& player)
{
  _cameraRect.x = player.tile()->x() * TILE_WIDTH  - (_cameraRect.w/2);
  _cameraRect.y = player.tile()->y() * TILE_HEIGHT - (_cameraRect.h/2);

  
  if(_cameraRect.x < 0) _cameraRect.x = 0;
  if(_cameraRect.y < 0) _cameraRect.y = 0;
  if(_cameraRect.x >= Level::LEVEL_WIDTH*TILE_WIDTH   - _cameraRect.w) _cameraRect.x = Level::LEVEL_WIDTH* TILE_WIDTH  - _cameraRect.w;
  if(_cameraRect.y >= Level::LEVEL_HEIGHT*TILE_HEIGHT - _cameraRect.h) _cameraRect.y = Level::LEVEL_HEIGHT*TILE_HEIGHT - _cameraRect.h;
}



void Renderer::render(Level& level)
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_main);
  renderLevel(level);
  renderMonsters(level);
  SDL_RenderSetViewport(_graphics->Renderer, NULL);
}

void Renderer::renderMonsters(Level& level)
{
  vector<Monster*> monsters = level.getMonsters();
  for(Monster* m : monsters)
  {
    if(m->dead())
      continue;
    auto currentTile = m->tile();
    auto lit = level.light_map(currentTile->x(), currentTile->y());
    if(lit != Level::LightType::Lit)
      continue;
    auto sprite = _monsters[(int)m->getMonsterType()];
    sprite->update(m->direction);
    draw_sprite(sprite, *currentTile);
    draw_health(*m);
  }
}

void Renderer::render_items(Tile& tile, int alpha)
{
  for(Item* item : tile.items())
  {
    _items[(int)item->item_type()]->draw(tile.x()*TILE_WIDTH, tile.y()*TILE_HEIGHT, _cameraRect.x, _cameraRect.y, alpha);
  }

}

void Renderer::renderLevel(Level& level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Level::LightType lit = level.light_map(x, y);
      if(lit != Level::LightType::Unseen)
      {
        int alpha = 255;
        if(lit == Level::LightType::Unlit)
          alpha = 64;
        else
        {
          auto intensity = level.light_intensity(x,y);
          alpha = static_cast<int>(255.0f * intensity);
          if(alpha < 64)
            alpha = 64;
        }

        //int alpha = lit == Level::LightType::Unlit ? 128 : 255;
        auto currentTile = level.getTile(x, y);
        auto tileType = (int)currentTile->tile_type();
        _mapTiles[tileType]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y, alpha);
        render_items(*currentTile, alpha);
      }
    }
  }
}


void Renderer::render(Player& player)
{
  auto currentTile = player.tile();
  _player->update(player.direction);
  draw_sprite(_player, *currentTile);
  draw_health(player);
}

void Renderer::draw_health(Actor& actor)
{
  if(actor.health() == actor.max_health())
    return;
  SDL_Rect health;
  health.x = actor.x()*TILE_WIDTH - _cameraRect.x;
  health.y = actor.y()*TILE_HEIGHT - _cameraRect.y + (TILE_HEIGHT-10);
  health.w = TILE_WIDTH;
  health.h = 5;

  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, 128);
  SDL_SetRenderDrawBlendMode(_graphics->Renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderDrawRect(_graphics->Renderer, &health);

  health.x++;
  health.y++;
  health.h-=2;
  health.w = 32.0f * (static_cast<float>(actor.health()) / actor.max_health()) - 2;
  SDL_SetRenderDrawColor(_graphics->Renderer, 255, 0, 0, 128);
  SDL_RenderFillRect(_graphics->Renderer, &health);
  SDL_SetRenderDrawBlendMode(_graphics->Renderer, SDL_BLENDMODE_NONE);
  SDL_SetRenderDrawColor(_graphics->Renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

void Renderer::render_info()
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_info);
  //auto vp_t = _graphics->loadTexture("../content/vp_info.png");
  //SDL_RenderCopy(_graphics->Renderer, vp_t, NULL, NULL);

}

void Renderer::render_messages()
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_msg);
  //auto vp_t = _graphics->loadTexture("../content/vp_msg.png");
  //SDL_RenderCopy(_graphics->Renderer, vp_t, NULL, NULL);
}

void Renderer::draw_sprite(Sprite* sprite, Tile& tile)
{
  sprite->draw(tile.x()*TILE_WIDTH, tile.y()*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);

}
