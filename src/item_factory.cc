#include "item_factory.h"
#include "item.h"
#include "potion.h"
#include <SDL2/SDL.h>

std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> ItemFactory::_prototypes;

Item* ItemFactory::Build()
{
  auto proto = ItemFactory::getProtoPotion(Item::ItemSubtype::POTION_HEALTH);
  auto newPotion =  new Potion(proto);
  return newPotion;
}

void ItemFactory::Init()
{
  ItemFactory::init_potions();
}

void ItemFactory::init_potions()
{
  ItemFactory::_prototypes[Item::ItemType::POTION][Item::ItemSubtype::POTION_HEALTH] = 
    new Potion("Small Health Potion", Item::ItemSubtype::POTION_HEALTH, {{Actor::Attribute::HEALTH, 25, 0}});
}

Potion& ItemFactory::getProtoPotion(Item::ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[Item::ItemType::POTION][subtype];
  return *static_cast<Potion*>(current);
  
}
