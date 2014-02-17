#include "item.h"

Item::Item(ItemType itemType)
{
  _item_type = itemType;
}

Item::~Item()
{
}

Item::ItemType Item::item_type()
{
  return _item_type;
}
