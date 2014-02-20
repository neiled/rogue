#include "item.h"

Item::Item(ItemType itemType, ItemSubtype subtype)
{
  _item_type = itemType;
  _item_subtype = subtype;
}

Item::~Item()
{
}

Item::ItemType Item::item_type()
{
  return _item_type;
}

Item::ItemSubtype Item::item_subtype()
{
  return _item_subtype;
}
