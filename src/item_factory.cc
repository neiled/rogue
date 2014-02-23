#include "item_factory.h"
#include "item.h"
#include "potion.h"
#include <SDL2/SDL.h>

std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> ItemFactory::_prototypes;

Item* ItemFactory::Build()
{
  SDL_Log("1a");
  auto proto = ItemFactory::getProtoPotion(Item::ItemSubtype::POTION_HEALTH);
  SDL_Log("2a");
  auto newPotion =  new Potion(proto);
  SDL_Log("3a");
  return newPotion;
}

void ItemFactory::Init()
{
  ItemFactory::init_potions();
}

void ItemFactory::init_potions()
{
  ItemFactory::_prototypes[Item::ItemType::POTION][Item::ItemSubtype::POTION_HEALTH] = 
    new Potion(Item::ItemSubtype::POTION_HEALTH, {{Actor::Attribute::HEALTH, 25, 0}});
}

Potion& ItemFactory::getProtoPotion(Item::ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[Item::ItemType::POTION][subtype];
  return *static_cast<Potion*>(current);
  
}
