#include "renderer.h"
#include "tile.h"

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  Sprite* sprite = new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, TILE_WIDTH, TILE_HEIGHT);
  _mapTiles.push_back(sprite);

  _player = new Sprite(_graphics, "../content/knt1_lf1.bmp", 0,0,32,32);
  
  _cameraRect.width = graphics->getScreenWidth();
  _cameraRect.height = screenHeight->getScreenHeight();
  _cameraRect.x = 0;
  _cameraRect.y = 0;
}

Renderer::~Renderer()
{
}

void Renderer::update(World* world, int elapsed_time_in_ms)
{
  updateCamera(world->getPlayer());
  updateLightMap(world->getPlayer());
}

void Renderer::updateCamera(Player* player)
{
  _cameraRect.x = player->getCurrentTile()->getX() - (_cameraRect.width/2);
  _cameraRect.y = player->getCurrentTile()->getY() - (_cameraRect.height/2);
  
  if(_cameraRect.x < 0) _cameraRect.x = 0;
  if(_cameraRect.y < 0) _cameraRect.y = 0;
  if(_cameraRect.x >= Level::LEVEL_WIDTH - _camera.width) _cameraRect.x = Level::LEVEL_WIDTH - _camera.width;
  if(_cameraRect.y >= Level::LEVEL_HEIGHT - _camera.height) _cameraRect.y = Level::LEVEL_HEIGHT - _camera.height;
}

void Renderer::updateLightMap(Player* player)
{
  int maxLightDistance = 5;
  int startLocationX = player->getCurrentTile()->getX() - maxLightDistance;
  int startLocationY = player->getCurrentTile()->getY() - maxLightDistance;
  int endLocationX = player->getCurrentTile()->getX() + maxLightDistance;
  int endLocationY = player->getCurrentTile()->getY() + maxLightDistance;

  if(startLocationX < 0) startLocationX = 0;
  if(startLocationY < 0) startLocationY = 0;
  if(endLocationX >= Level::LEVEL_WIDTH) endLocationX = Level::LEVEL_WIDTH;
  if(endLocationY >= Level::LEVEL_HEIGHT) endLocationY = Level::LEVEL_HEIGHT;

   
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      _light_map[y][x] = false;
    }
  }

  for (int y = startLocationY; y < endLocationY; ++y)
  {
    for (int x = startLocationX; x < endLocationX; ++x)
    {
     _light_map[y][x] = true; 
    }
  }
}

void Renderer::render(Level* level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      bool lit = _light_map[y][x];
      Tile* currentTile = level->getTile(x, y);
      if(currentTile->getTileType() == Tile::TileType::Rock && lit)
        _mapTiles[0]->draw(x*TILE_WIDTH,y*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);
    }
  }
}

void Renderer::render(Player* player)
{
  Tile* currentTile = player->getCurrentTile();
  _player->draw(currentTile->getX()*TILE_WIDTH, currentTile->getY()*TILE_HEIGHT, _cameraRect.x, _cameraRect.y);
}

