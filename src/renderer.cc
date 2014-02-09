#include "renderer.h"
#include "tile.h"
#include "sprite.h"
#include "directional_sprite.h"
#include "graphics.h"
#include "player.h"
#include "level.h"

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  _mapTiles[(int)Tile::TileType::Floor] =  new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, TILE_WIDTH, TILE_HEIGHT);
  //_mapTiles.push_back(sprite);

  _mapTiles[(int)Tile::TileType::StairsUp] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_WIDTH, 2*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
  //_mapTiles.push_back(sprite);

  _mapTiles[(int)Tile::TileType::StairsDown] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 11*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
  //_mapTiles.push_back(sprite);

  _mapTiles[(int)Tile::TileType::Rock] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 12*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

  _mapTiles[(int)Tile::TileType::Door] = new Sprite(_graphics, "../content/dungeon_tiles_32.bmp", 13*TILE_WIDTH, 5*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

  //_player = new Sprite(_graphics, "../content/knt1_lf1.bmp", 0,0,32,32);
  //_player = new Sprite(_graphics, "../content/player_right.png", 0,0,32,32);
  _player = new DirectionalSprite(_graphics, "../content/player.png", 0, 0, TILE_WIDTH, TILE_HEIGHT);
  
  _cameraRect.w= graphics->getScreenWidth();
  _cameraRect.h= graphics->getScreenHeight();
  _cameraRect.x = 0;
  _cameraRect.y = 0;
}

Renderer::~Renderer()
{
}

void Renderer::update(World* world, int elapsed_time_in_ms)
{
  updateCamera(world->getPlayer());
}

void Renderer::updateCamera(Player* player)
{
  _cameraRect.x = player->getCurrentTile()->getX() * TILE_WIDTH  - (_cameraRect.w/2);
  _cameraRect.y = player->getCurrentTile()->getY() * TILE_HEIGHT - (_cameraRect.h/2);

  
  if(_cameraRect.x < 0) _cameraRect.x = 0;
  if(_cameraRect.y < 0) _cameraRect.y = 0;
  if(_cameraRect.x >= Level::LEVEL_WIDTH*TILE_WIDTH   - _cameraRect.w) _cameraRect.x = Level::LEVEL_WIDTH* TILE_WIDTH  - _cameraRect.w;
  if(_cameraRect.y >= Level::LEVEL_HEIGHT*TILE_HEIGHT - _cameraRect.h) _cameraRect.y = Level::LEVEL_HEIGHT*TILE_HEIGHT - _cameraRect.h;
}



void Renderer::render(Level* level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Level::LightType lit = level->getTileLightMap(x, y);
      if(lit != Level::LightType::Unseen)
      {
        int alpha = lit == Level::LightType::Unlit ? 128 : 255;
        Tile* currentTile = level->getTile(x, y);
        _mapTiles[(int)currentTile->getTileType()]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y, alpha);

        //if(currentTile->getTileType() == Tile::TileType::Rock)
          //_mapTiles[0]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);
        //else if(currentTile->getTileType() == Tile::TileType::StairsUp)
          //_mapTiles[1]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);
        //else if(currentTile->getTileType() == Tile::TileType::StairsDown)
          //_mapTiles[2]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);

      }
    }
  }
}

void Renderer::render(Player* player)
{
  Tile* currentTile = player->getCurrentTile();
  _player->update(player->direction);
  _player->draw(currentTile->getX()*TILE_WIDTH, currentTile->getY()*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);
}

