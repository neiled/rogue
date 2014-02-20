#include "inventory.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::add(Item* item)
{
  _items.push_back(item);
}
