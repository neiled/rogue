#include "inventory.h"
#include "item.h"
#include "potion.h"
#include "actor.h"
#include <SDL2/SDL.h>

Inventory::Inventory(Actor* actor)
{
  _actor = actor;
}

Inventory::~Inventory()
{
  for(auto item : _items)
    delete item;
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
  if(index >= _items.size())
    return;
  auto item = _items.at(index);
  if(item->item_type() == Item::ItemType::POTION)
  {
    auto potion = static_cast<Potion*>(item);
    potion->drink(*_actor);
  }
  remove(item);
}
