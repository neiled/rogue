#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>


class Item;
class Actor;
class Tile;

class Inventory
{
public:
  Inventory(int max_items);
  virtual ~Inventory ();
  void add(Item* item);
  void remove(Item* item);
  Item* remove(int index);
  std::vector<Item*> items();
  void clear();
  bool empty();
  bool full();
  int count();
  int max_items();
  void use(Item* item, Actor& actor);
  void drop(Item* item, Tile& tile);

private:
  std::vector<Item*> _items;
  int _max_items;
};
#endif
