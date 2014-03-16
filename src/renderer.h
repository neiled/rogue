#ifndef RENDERER_H_
#define RENDERER_H_


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
#include "render_level.h"
#include "render_info.h"
#include "game_types.h"

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
class Game;
struct Message;



class Renderer {
  public:
    Renderer(Graphics* graphics);
    ~Renderer();

    void init();
  
    void render(Game& game);
    void update(World* world);

    const static int TILE_SIZE = 32;

    void draw_sprite(Sprite* sprite, Tile& tile);
    void draw_health(Actor& actor);
    void render_string(std::string message, int x, int y, int h);
    void render_message(std::vector<Message> messages, int x, int y, int h);
    Tile* get_tile_from_coord(Level& level, int x, int y);
    
    void draw_health_bar(int x, int y, int width, int height, int health, int max_health, int previous_health);
    void draw_xp_bar(int x, int y, int width, int height, int current, int max);
  private:
    //array<Sprite*,5> _mapTiles;
    monster_sprites_t _monsters;
    item_sprites_t _items;
    level_sprites_t _tiles;
    DirectionalSprite* _player = nullptr;
    Graphics* _graphics = nullptr;

    RenderInventory _render_inv;
    RenderInfo _render_info;
    RenderLevel _render_level;

    SDL_Rect _vp_main;
    SDL_Rect _vp_msg;
    SDL_Rect _vp_info;

    void updateCamera(Player& player);
    void loadMapTiles();
    void loadMonsterTiles();
    void init_viewports();
    void draw_bar(int x, int y, int width, int height, int health, int max_health, int r, int g, int b, bool background = true);

    void render_level(Level& level);
    void render_monsters(Level& level);
    void render_items(Tile& tile, int alpha);
    SDL_Texture* render_message(std::string message, int height, SDL_Color color = SDL_Color{255,255,255});

    
    SDL_Rect _cameraRect;
    
    void load_items();
    void load_corpses();
    void load_potions();
    void load_weapons();
    void load_scrolls();
    void load_scenery();

    void render(Level& level);
    void render(Player& player);
    
    void render_player_info(Game& game, Player& player);
    void render_actor_info(Game& game, Actor* actor);
    void render_info(Game& game, Player& player);
    
    void render_messages(std::deque<std::vector<Message>> messages);
    void render_state(GameState state, Player& player);
    void render_inventory(Inventory& inventory);
    void render_chest(Inventory& inventory);

    SDL_Color calc_color(MessageType type);


};
#endif
