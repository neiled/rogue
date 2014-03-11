#include "weapon.h"
#include <sstream>

Weapon::Weapon(std::string name, ItemSubtype subtype, int max_damage, int min_damage, std::vector<AttributeModifiers> modifiers)
  : _min_damage(min_damage), _max_damage(max_damage), Item(name, ItemType::WEAPON, subtype, modifiers)
{
}

Weapon::Weapon(Weapon& other) : Item(other), _max_damage(other.max_damage()), _min_damage(other.min_damage())
{
}


Weapon::~Weapon()
{
}

int Weapon::max_damage()
{
  return _max_damage;
}

int Weapon::min_damage()
{
  return _min_damage;
}


std::string Weapon::name()
{
  std::ostringstream s;
  s << _name << " (" << max_damage() << ")";
  return s.str();
}
