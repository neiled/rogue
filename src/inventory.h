#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>

class Item;

class Inventory
{
public:
  Inventory ();
  virtual ~Inventory ();
  void add(Item* item);
  std::vector<Item*> items();
  void empty();

private:
  std::vector<Item*> _items;
};
#endif
