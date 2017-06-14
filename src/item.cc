#include "item.h"


Item::Item(std::string name, ItemType itemType, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers ) : GameObject(name)
{
  _item_type = itemType;
  _item_subtype = subtype;
  _modifiers = modifiers;
}

Item::Item(std::string name, ItemType itemType, ItemSubtype subtype) : Item(name, itemType, subtype, std::vector<AttributeModifiers>())
{
}

Item::~Item()
{
}

Item::Item(Item& other) : GameObject(other)
{
  _item_type = other._item_type;
  _item_subtype = other._item_subtype;
  _modifiers = other._modifiers;
  _name = other._name;
}

ItemType Item::item_type()
{
  return _item_type;
}

ItemSubtype Item::item_subtype()
{
  return _item_subtype;
}



bool Item::interesting()
{
  return _item_type != ItemType::CORPSE;
}

bool Item::can_pick_up()
{
  return _item_type != ItemType::CORPSE;
}

std::vector<AttributeModifiers> Item::modifiers()
{
  return _modifiers;
}

void Item::modifiers(std::vector<AttributeModifiers> modifiers)
{
  _modifiers = modifiers;
}
