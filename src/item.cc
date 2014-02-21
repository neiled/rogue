#include "item.h"
#include <SDL2/SDL.h>

Item::Item(ItemType itemType, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers )
{
  _item_type = itemType;
  _item_subtype = subtype;
  _modifiers = modifiers;
}

Item::Item(ItemType itemType, ItemSubtype subtype) : Item(itemType, subtype, std::vector<AttributeModifiers>())
{
}

Item::~Item()
{
}

Item::Item(Item& other)
{
  _item_type = other._item_type;
  _item_subtype = other._item_subtype;
  _modifiers = other._modifiers;
}

Item::ItemType Item::item_type()
{
  return _item_type;
}

Item::ItemSubtype Item::item_subtype()
{
  return _item_subtype;
}
