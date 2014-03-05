#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>


class Item;
class Actor;

class Inventory
{
public:
  Inventory(int max_items);
  virtual ~Inventory ();
  void add(Item* item);
  void remove(Item* item);
  std::vector<Item*> items();
  void empty();
  bool full();
  int count();
  int max_items();
  void use(int index, Actor& actor);

private:
  std::vector<Item*> _items;
  int _max_items;
};
#endif
