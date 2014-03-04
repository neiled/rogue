#include "weapon.h"

Weapon::Weapon(std::string name, Item::ItemSubtype subtype, int max_damage, std::vector<AttributeModifiers> modifiers)
  : _max_damage(max_damage), Item(name, Item::ItemType::WEAPON, subtype, modifiers)
{
}


Weapon::~Weapon()
{
}

int Weapon::max_damage()
{
  return _max_damage;
}

int Weapon::calc_damage()
{
  return _max_damage;
}
