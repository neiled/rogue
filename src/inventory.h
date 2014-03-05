#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>


class Item;
class Actor;

class Inventory
{
public:
  Inventory();
  virtual ~Inventory ();
  void add(Item* item);
  void remove(Item* item);
  std::vector<Item*> items();
  void empty();
  bool full();
  int count();
  void use(int index, Actor& actor);

private:
  std::vector<Item*> _items;
};
#endif
