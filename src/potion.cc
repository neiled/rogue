#include "potion.h"
#include "messages.h"
#include <string>

Potion::Potion(std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, Item::ItemType::POTION, subtype, modifiers)
{
}

Potion::~Potion()
{
}

void Potion::drink(Actor& actor)
{
  //TODO: drink the potion
  Messages::Add("You drink the " + _name);
  for(auto attribute_modifier : _modifiers)
  {
    actor.add_modifier(&attribute_modifier);
  }
}
