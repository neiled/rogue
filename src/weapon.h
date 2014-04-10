#ifndef WEAPON_H
#define WEAPON_H 

#include "item.h"
#include "game_types.h"

class Actor;

class Weapon : public Item
{
public:
  Weapon(std::string name, ItemType type, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers);
  Weapon(std::string name, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers);
  Weapon(Weapon& other);
  virtual ~Weapon ();
  
  virtual int max_damage() override;
  virtual int min_damage() override;

  virtual std::string name() override;
  std::string damage_name();
  
private:
  int _max_damage;
  int _min_damage;
  int damage_modifier();
};
#endif
