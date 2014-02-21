#include "potion.h"

Potion::Potion(Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(Item::ItemType::POTION, subtype, modifiers)
{
}

Potion::~Potion()
{
}

void Potion::drink(Actor& actor)
{
  //TODO: drink the potion
}
