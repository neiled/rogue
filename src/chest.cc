#include "chest.h"

Chest::Chest() : _inventory(10), Item("Chest", ItemType::CHEST, ItemSubtype::CHEST)
{
}

Chest::~Chest()
{
}

Inventory* Chest::inventory()
{
  return &_inventory;
}
