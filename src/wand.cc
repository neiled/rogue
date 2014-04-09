#include "wand.h"

Wand::Wand(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers, int range) : RangedWeapon(name, subtype, 0, 0, modifiers, range)
{
}

Wand::Wand(Wand& other) : RangedWeapon(other)
{
}

Wand::~Wand()
{}
