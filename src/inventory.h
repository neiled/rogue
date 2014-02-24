#ifndef INVENTORY_H
#define INVENTORY_H 

#include <vector>


class Item;
class Actor;

class Inventory
{
public:
  Inventory (Actor* actor);
  virtual ~Inventory ();
  void add(Item* item);
  void remove(Item* item);
  std::vector<Item*> items();
  void empty();
  void use(int index);

private:
  std::vector<Item*> _items;
  Actor* _actor;
};
#endif
