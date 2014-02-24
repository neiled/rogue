#include "inventory.h"
#include "item.h"
#include "potion.h"
#include "actor.h"

Inventory::Inventory(Actor* actor)
{
  _actor = actor;
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

void Inventory::remove(Item* item)
{
  _items.erase(std::remove(_items.begin(), _items.end(), item), _items.end());
}

void Inventory::use(int index)
{
  auto item = _items[index];
  if(item->item_type() == Item::ItemType::POTION)
  {
    auto potion = static_cast<Potion*>(item);
    potion->drink(*_actor);
  }
  remove(item);
}
