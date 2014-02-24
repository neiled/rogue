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
    void update(World* world, int elapsed_time_in_ms);

    const static int TILE_SIZE = 32;
    
  private:
    array<Sprite*,5> _mapTiles;
    array<DirectionalSprite*, 1> _monsters;
    std::map<Item::ItemType, std::map<Item::ItemSubtype, Sprite*>> _items;
    DirectionalSprite* _player = nullptr;
    Graphics* _graphics = nullptr;
    Sprite* _info_char = nullptr;

    SDL_Rect _vp_main;
    SDL_Rect _vp_msg;
    SDL_Rect _vp_info;

    void updateCamera(Player& player);
    void loadMapTiles();
    void loadMonsterTiles();
    void load_info();
    void init_viewports();
    void draw_health_bar(int x, int y, int width, int height, int health, int max_health);

    void renderLevel(Level& level);
    void renderMonsters(Level& level);
    void render_items(Tile& tile, int alpha);
    SDL_Texture* render_message(std::string message, int height);

    void draw_sprite(Sprite* sprite, Tile& tile);
    void draw_health(Actor& actor);
    
    SDL_Rect _cameraRect;
    
    void load_items();
    void load_corpses();
    void load_potions();

    void render(Level& level);
    void render(Player& player);
    void render_info(Player& player);
    void render_messages(std::deque<std::string> messages);
    void render_state(Game::GameState state, Player& player);
    void render_inventory(Inventory& inventory);


};
#endif
