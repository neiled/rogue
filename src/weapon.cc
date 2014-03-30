#include "weapon.h"
#include <sstream>

Weapon::Weapon(std::string name, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers)
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

int Weapon::damage_modifier()
{
  for(auto current_attr_mod : _modifiers)
  {
    if(current_attr_mod.attr() == Actor::Attribute::DMG)
      return current_attr_mod.modifier();
  }
  return 0;
}


std::string Weapon::name()
{
  std::ostringstream s;
  s << _name << " (" << min_damage() << "-" << max_damage() << ")";
  int dmg_mod = damage_modifier();
  if(dmg_mod > 0)
    s << " + " << dmg_mod;
  return s.str();
}

std::string Weapon::damage_name()
{
  std::ostringstream s;
  s << min_damage() << "-" << max_damage();
  auto modifier = damage_modifier();
  if(modifier > 0)
    s << " + " << modifier;
  return s.str();
}
