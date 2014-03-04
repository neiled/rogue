#ifndef WEAPON_H
#define WEAPON_H 

#include "item.h"

class Weapon : public Item
{
public:
  Weapon(std::string name, Item::ItemSubtype subtype, int max_damage, std::vector<AttributeModifiers> modifiers);
  virtual ~Weapon ();
  
  virtual int calc_damage(Actor&) override;
  
private:
  int _max_damage;
};
#endif
