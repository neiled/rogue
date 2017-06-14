#include "potion.h"
#include "messages.h"

Potion::Potion(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, ItemType::POTION, subtype, modifiers)
{
}

Potion::~Potion()
{
}

void Potion::drink(Actor& actor)
{
  Messages::Add("You drink the " + _name);
  for(auto attribute_modifier : _modifiers)
  {
    actor.add_modifier(attribute_modifier);
  }
}
