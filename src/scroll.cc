#include "scroll.h"

Scroll::Scroll(std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, Item::ItemType::SCROLL, subtype, modifiers)
{
}

Scroll::~Scroll()
{
}
