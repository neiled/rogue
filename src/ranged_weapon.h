#ifndef RANGED_WEAPON_H
#define RANGED_WEAPON_H 

#include "weapon.h"

class RangedWeapon : public Weapon
{
public:
  RangedWeapon (std::string name, ItemType type, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers, int range);
  RangedWeapon (std::string name, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers, int range);
  RangedWeapon(RangedWeapon& other);
  virtual ~RangedWeapon ();
  virtual void fire(Actor& owner, Tile& tile);

protected:
  int _range;
};
#endif
