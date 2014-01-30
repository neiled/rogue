#include "renderer.h"

Renderer::Renderer(Graphics* graphics)
{
  _graphics = graphics;
  Sprite* sprite = new Sprite(_graphics, "../content/dungeon_tiles_0.bmp", 64, 64, 16, 16);

  _mapTiles.push_back(sprite);
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
        _mapTiles[0]->draw(x*16,y*16);
    }
  }
}
