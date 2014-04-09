#ifndef WAND_H
#define WAND_H 

#include "ranged_weapon.h"

class Wand : public RangedWeapon
{
public:
  Wand (std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers, int range);
  Wand(Wand& other);
  virtual ~Wand ();

private:
  /* data */
};
#endif
