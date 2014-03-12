#include "inventory.h"
#include "item.h"
#include "potion.h"
#include "scroll.h"
#include "actor.h"
#include <SDL2/SDL.h>
#include <assert.h>
#include "random.h"
#include "messages.h"
#include "tile.h"

Inventory::Inventory(int max_items) : _max_items(max_items)
{
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

void Inventory::clear()
{
  _items.clear();
}

void Inventory::remove(Item* item)
{
  _items.erase(std::remove(_items.begin(), _items.end(), item), _items.end());
}

void Inventory::use(int index, Actor& actor)
{
  if(index >= _items.size())
    return;
  auto item = _items.at(index);
  if(item->item_type() == ItemType::POTION)
  {
    auto potion = static_cast<Potion*>(item);
    potion->drink(actor);
  }
  else if(item->item_type() == ItemType::WEAPON)
  {
    if(actor.weapon())
      add(actor.weapon());
    actor.weapon(item);
    Messages::Add("You start to wield the " + item->name());
  }
  else if(item->item_type() == ItemType::SCROLL)
  {
    auto scroll = static_cast<Scroll*>(item);
    scroll->cast(actor, nullptr);
  }
  remove(item);
}

void Inventory::drop(int index, Tile& tile)
{
  if(index >= _items.size())
    return;
  auto item = _items.at(index);
  remove(item);
  tile.add_item(item);
  Messages::Add("You drop the " + item->name());
}

Item* Inventory::remove(int index)
{
  if(index >= _items.size())
    return nullptr;
  auto item = _items.at(index);
  remove(item);
  return item;
}

bool Inventory::full()
{
  return _items.size() >= _max_items;
}

bool Inventory::empty()
{
  return _items.size() == 0;
}

int Inventory::count()
{
  return _items.size();
}

int Inventory::max_items()
{
  return _max_items;
}
