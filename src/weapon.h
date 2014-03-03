#ifndef WEAPON_H
#define WEAPON_H 

#include "item.h"

class Weapon : public Item
{
public:
  Weapon(std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  virtual ~Weapon ();

private:
  /* data */
};
#endif
