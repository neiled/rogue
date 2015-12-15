#ifndef RENDER_INVENTORY_H
#define RENDER_INVENTORY_H

#include <SDL2/SDL.h>
#include <vector>
#include "game_types.h"

class Renderer;
class Inventory;
class Sprite;
class Graphics;
class Item;


class RenderInventory
{
public:
    RenderInventory(Graphics* graphics);
    void render(Renderer& renderer, item_sprites_t items, std::vector<Item*> Inventory, SDL_Rect vp);
    void render_player_inventory(Renderer renderer, item_sprites_t items, Inventory &inventory);
    void render_chest_inventory(Renderer& renderer, item_sprites_t items, Inventory& Inventory);
    void render_player_wands(Renderer& renderer, item_sprites_t items, Inventory& inventory);
    void init();
private:
    Graphics* _graphics;
    SDL_Texture* _panel;

};
#endif
