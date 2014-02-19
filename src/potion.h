#ifndef POTION_H
#define POTION_H
#include "item.h"
#include "actor.h"

class Potion : public Item
{
public:
  Potion ();
  virtual ~Potion ();
  void drink(Actor& actor)

private:
  /* data */
};
#endif
