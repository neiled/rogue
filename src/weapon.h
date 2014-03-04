#ifndef WEAPON_H
#define WEAPON_H 

#include "item.h"

class Actor;

class Weapon : public Item
{
public:
  Weapon(std::string name, Item::ItemSubtype subtype, int max_damage, std::vector<AttributeModifiers> modifiers);
  Weapon(Weapon& other);
  virtual ~Weapon ();
  
  virtual int max_damage() override;
  virtual int calc_damage(Actor&) override;
  
private:
  int _max_damage;
};
#endif
