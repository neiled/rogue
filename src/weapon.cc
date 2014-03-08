#include "weapon.h"
#include <sstream>

Weapon::Weapon(std::string name, ItemSubtype subtype, int max_damage, std::vector<AttributeModifiers> modifiers)
  : _max_damage(max_damage), Item(name, ItemType::WEAPON, subtype, modifiers)
{
}

Weapon::Weapon(Weapon& other) : Item(other), _max_damage(other.max_damage())
{
}


Weapon::~Weapon()
{
}

int Weapon::max_damage()
{
  return _max_damage;
}

int Weapon::calc_damage(Actor& other)
{
  return _max_damage;
}

std::string Weapon::name()
{
  std::ostringstream s;
  s << _name << " (" << max_damage() << ")";
  return s.str();
}
