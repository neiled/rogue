#ifndef TILE_H_
#define TILE_H_

#include <vector>
#include "game_types.h"

class Level;
class Actor;
class Item;

class Tile
{
  public:


    Tile (TileType tileType, Level& level, int x, int y);
    virtual ~Tile ();
    void setTileType(TileType tileType);
    double distanceTo(const Tile& otherTile);
    void removeActor();
    void setActor(Actor& actor);
    void add_item(Item* item);
    void remove_item(Item* item);
    
    Actor* actor();
    Level& level();
    std::vector<Item*> items();
    TileType tile_type();
    int x() const;
    int y() const;
    bool is_lit() const;
    bool interesting();
    std::string name();


  private:
    TileType _tileType;
    int _x;
    int _y;
    Level& _level;
    Actor* _actor = nullptr;
    std::vector<Item*> _items;
};
#endif
