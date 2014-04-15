#ifndef WAND_H
#define WAND_H 

#include "ranged_weapon.h"

class Wand : public RangedWeapon
{
public:
  Wand (std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers, int range);
  Wand(Wand& other);
  virtual ~Wand ();
  virtual void fire(Actor& owner, Tile& tile) override;

private:
  void flame(Actor& owner, Tile& tile);
  int _charges;
};
#endif
