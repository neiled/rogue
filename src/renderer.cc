#include "renderer.h"

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  Sprite* sprite = new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, TILE_WIDTH, TILE_HEIGHT);
  _mapTiles.push_back(sprite);

  _player = new Sprite(_graphics, "../content/knt1_lf1.bmp", 0,0,32,32);
}

Renderer::~Renderer()
{
}

void Renderer::render(Level* level)
{
  for (int y = 0; y < Level::LEVEL_HEIGHT; ++y)
  {
    for (int x = 0; x < Level::LEVEL_WIDTH; ++x)
    {
      Tile* currentTile = level->getTile(x, y);
      if(currentTile->getTileType() == Tile::TileType::Rock)
        _mapTiles[0]->draw(x*TILE_WIDTH,y*TILE_HEIGHT);
    }
  }
}

void Renderer::render(Player* player)
{
  Tile* currentTile = player->getCurrentTile();
  _player->draw(currentTile->getX(), currentTile->getY());
}

