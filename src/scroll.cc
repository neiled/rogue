#include "scroll.h"

Scroll::Scroll(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, ItemType::SCROLL, subtype, modifiers)
{
}

Scroll::~Scroll()
{
}
