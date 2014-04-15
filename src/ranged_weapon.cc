#include "ranged_weapon.h"

RangedWeapon::RangedWeapon(std::string name, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers, int range) : Weapon(name, ItemType::RANGED, subtype, min_damage, max_damage, modifiers), _range(range)
{

}

RangedWeapon::RangedWeapon(std::string name, ItemType type, ItemSubtype subtype, int min_damage, int max_damage, std::vector<AttributeModifiers> modifiers, int range) : Weapon(name, type, subtype, min_damage, max_damage, modifiers), _range(range)
{

}

RangedWeapon::RangedWeapon(RangedWeapon& other) : Weapon(other)
{
  _range = other._range;
}

RangedWeapon::~RangedWeapon()
{
}

void RangedWeapon::fire(Actor& owner, Tile& target)
{
}
