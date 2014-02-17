#ifndef RENDERER_H_
#define RENDERER_H_


#include <vector>
#include <array>
#include <SDL2/SDL.h>
#include <SDL2_Image/SDL_Image.h>

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
  
    void render(Level& level);
    void render(Player& player);
    void render_info();
    void render_messages();
    void update(World* world, int elapsed_time_in_ms);

    const static int TILE_WIDTH = 32;
    const static int TILE_HEIGHT = 32;
    
  private:
    array<Sprite*,5> _mapTiles;
    array<DirectionalSprite*, 1> _monsters;
    array<Sprite*, 1> _items;
    DirectionalSprite* _player = nullptr;
    Graphics* _graphics = nullptr;

    SDL_Rect _vp_main;
    SDL_Rect _vp_msg;
    SDL_Rect _vp_info;

    void updateCamera(Player& player);
    void loadMapTiles();
    void loadMonsterTiles();
    void load_items();
    void init_viewports();

    void renderLevel(Level& level);
    void renderMonsters(Level& level);
    void render_items(Tile& tile, int alpha);

    void draw_sprite(Sprite* sprite, Tile& tile);
    void draw_health(Actor& actor);
    
    SDL_Rect _cameraRect;
    


};
#endif
