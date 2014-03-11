#ifndef WEAPON_H
#define WEAPON_H 

#include "item.h"
#include "game_types.h"

class Actor;

class Weapon : public Item
{
public:
  Weapon(std::string name, ItemSubtype subtype, int max_damage, std::vector<AttributeModifiers> modifiers);
  Weapon(Weapon& other);
  virtual ~Weapon ();
  
  virtual int max_damage() override;
  virtual int min_damage() override;
  //virtual int calc_damage(Actor&) override;

  virtual std::string name() override;
  
private:
  int _max_damage;
};
#endif
