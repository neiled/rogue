#include "renderer.h"
#include "tile.h"
#include "sprite.h"
#include "directional_sprite.h"
#include "graphics.h"
#include "player.h"
#include "level.h"
#include "monster.h"
#include "world.h"

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  loadMapTiles();
  loadMonsterTiles();

  _player = new DirectionalSprite(_graphics, "../content/player.png", 0, 0, TILE_WIDTH, TILE_HEIGHT);

  int screen_h = graphics->getScreenHeight();
  int screen_w = graphics->getScreenWidth();
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

Renderer::~Renderer()
{
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

void Renderer::update(World* world, int elapsed_time_in_ms)
{
  updateCamera(world->getPlayer());
}

void Renderer::updateCamera(Player& player)
{
  _cameraRect.x = player.getCurrentTile()->x() * TILE_WIDTH  - (_cameraRect.w/2);
  _cameraRect.y = player.getCurrentTile()->y() * TILE_HEIGHT - (_cameraRect.h/2);

  
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
    auto currentTile = m->getCurrentTile();
    auto lit = level.getTileLightMap(currentTile->x(), currentTile->y());
    if(lit != Level::LightType::Lit)
      continue;
    auto sprite = _monsters[(int)m->getMonsterType()];
    sprite->update(m->direction);
    drawSprite(sprite, *currentTile);
  }
}

void Renderer::renderLevel(Level& level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Level::LightType lit = level.getTileLightMap(x, y);
      if(lit != Level::LightType::Unseen)
      {
        int alpha = lit == Level::LightType::Unlit ? 128 : 255;
        auto currentTile = level.getTile(x, y);
        auto tileType = (int)currentTile->getTileType();
        _mapTiles[tileType]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y, alpha);
      }
    }
  }
}


void Renderer::render(Player& player)
{
  auto currentTile = player.getCurrentTile();
  _player->update(player.direction);
  drawSprite(_player, *currentTile);
}

void Renderer::render_info()
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_info);
  auto vp_t = _graphics->loadTexture("../content/vp_info.png");
  SDL_RenderCopy(_graphics->Renderer, vp_t, NULL, NULL);

}

void Renderer::render_messages()
{
  SDL_RenderSetViewport(_graphics->Renderer, &_vp_msg);
  auto vp_t = _graphics->loadTexture("../content/vp_msg.png");
  SDL_RenderCopy(_graphics->Renderer, vp_t, NULL, NULL);
}

void Renderer::drawSprite(Sprite* sprite, Tile& tile)
{
  sprite->draw(tile.x()*TILE_WIDTH, tile.y()*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);

}
