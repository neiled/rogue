#ifndef CHEST_H
#define CHEST_H 

#include "item.h"
#include "inventory.h"

class Chest : public Item
{
public:
  Chest ();
  virtual ~Chest ();
  virtual bool interesting() override {return true;}
  virtual bool can_pick_up() override {return false;}
  Inventory* inventory();

private:
  Inventory _inventory;
  
};
#endif
