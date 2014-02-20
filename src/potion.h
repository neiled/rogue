#ifndef POTION_H
#define POTION_H
#include "item.h"
#include "actor.h"

class Potion : public Item
{
public:
  Potion (Item::ItemSubtype subtype);
  virtual ~Potion ();
  void drink(Actor& actor);

private:
  /* data */
};
#endif
