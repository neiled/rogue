#ifndef RENDERER_H_
#define RENDERER_H_


#include "game.h"
#include "item.h"
#include <vector>
#include <array>
#include <deque>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include "render_inventory.h"

using std::vector;
using std::array;

class Player;
class Sprite;
class DirectionalSprite;
class World;
class Graphics;
class Level;
class Monster;
class Tile;
class Actor;

class Renderer {
  public:
    Renderer(Graphics* graphics);
    ~Renderer();
  
    void render(Game& game);
    void update(World* world);

    const static int TILE_SIZE = 32;

    void draw_sprite(Sprite* sprite, Tile& tile);
    void draw_health(Actor& actor);
    void render_string(std::string message, int x, int y, int h);
    
  private:
    array<Sprite*,5> _mapTiles;
    Game::monster_sprites_t _monsters;
    Game::item_sprites_t _items;
    DirectionalSprite* _player = nullptr;
    Graphics* _graphics = nullptr;
    Sprite* _info_char = nullptr;

    RenderInventory _render_inv;

    SDL_Rect _vp_main;
    SDL_Rect _vp_msg;
    SDL_Rect _vp_info;

    void updateCamera(Player& player);
    void loadMapTiles();
    void loadMonsterTiles();
    void load_info();
    void init_viewports();
    void draw_health_bar(int x, int y, int width, int height, int health, int max_health);

    void render_level(Level& level);
    void render_monsters(Level& level);
    void render_items(Tile& tile, int alpha);
    SDL_Texture* render_message(std::string message, int height);

    
    SDL_Rect _cameraRect;
    
    void load_items();
    void load_corpses();
    void load_potions();
    void load_weapons();

    void render(Level& level);
    void render(Player& player);
    void render_info(Player& player);
    void render_messages(std::deque<std::string> messages);
    void render_state(Game::GameState state, Player& player);
    void render_inventory(Inventory& inventory);


};
#endif
