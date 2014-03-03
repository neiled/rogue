#include "weapon.h"

Weapon::Weapon(std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, Item::ItemType::WEAPON, subtype, modifiers)
{
}


Weapon::~Weapon()
{
}
