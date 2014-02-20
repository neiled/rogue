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

std::vector<Item*> Inventory::items()
{
  return _items;
}

void Inventory::empty()
{
  _items.clear();
}
