#ifndef TILE_H_
#define TILE_H_

#include <vector>

class Level;
class Actor;
class Item;

class Tile
{
  public:
    enum struct TileType {Floor = 0, Rock=1, StairsDown=2, StairsUp=3, Door=4};


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


  private:
    TileType _tileType;
    int _x;
    int _y;
    Level& _level;
    Actor* _actor = nullptr;
    std::vector<Item*> _items;
};
#endif
