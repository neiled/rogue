#include "potion.h"

Potion::Potion(Item::ItemSubtype subtype) : Item(Item::ItemType::POTION, subtype)
{
}

Potion::~Potion()
{
}

void Potion::drink(Actor& actor)
{
  //TODO: drink the potion
}
