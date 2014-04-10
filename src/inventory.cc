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
std::vector<Item*> Inventory::items_of_type(ItemType type)
{
  auto result = std::vector<Item*>();
  for(auto current : _items)
  {
    if(current->item_type() == type)
      result.push_back(current);
  }

  return result;
}

void Inventory::clear()
{
  _items.clear();
}

void Inventory::remove(Item* item)
{
  _items.erase(std::remove(_items.begin(), _items.end(), item), _items.end());
}

void Inventory::use(Item* item, Actor& actor)
{
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
  else if(item->item_type() == ItemType::WAND)
  {
    //TODO: Something?
  }
  else
  {
    SDL_Log("Inventory doesn't know how to use that type of item!");
    return;
  }
  remove(item);
}

void Inventory::drop(Item* item, Tile& tile)
{
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
