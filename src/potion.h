#ifndef POTION_H
#define POTION_H
#include "item.h"
#include "actor.h"
#include "attribute_modifiers.h"
#include <string>

class Potion : public Item
{
public:
  Potion (std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  virtual ~Potion ();
  void drink(Actor& actor);

private:
  /* data */
};
#endif
