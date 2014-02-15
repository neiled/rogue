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
    DirectionalSprite* _player = nullptr;
    Graphics* _graphics = nullptr;

    SDL_Rect _vp_main;
    SDL_Rect _vp_msg;
    SDL_Rect _vp_info;

    void updateCamera(Player& player);
    void loadMapTiles();
    void loadMonsterTiles();

    void renderLevel(Level& level);
    void renderMonsters(Level& level);

    void drawSprite(Sprite* sprite, Tile& tile);
    
    SDL_Rect _cameraRect;
    


};
#endif
