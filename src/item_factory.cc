#include "item_factory.h"
#include "item.h"
#include "potion.h"
#include <SDL2/SDL.h>

std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> ItemFactory::_prototypes;

Item* ItemFactory::Build()
{
  return ItemFactory::get_potion(Item::ItemSubtype::POTION_HEALTH);
}

Item* ItemFactory::Build(Monster::MonsterType monster_type, int xp_level)
{
  auto item_type = ItemFactory::calc_item_type(monster_type, xp_level);
  auto item_subtype = ItemFactory::calc_item_subtype(item_type, monster_type, xp_level);
  return ItemFactory::get_item(item_type, item_subtype);
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

Potion* ItemFactory::get_potion(Item::ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[Item::ItemType::POTION][subtype];
  auto potion =  static_cast<Potion*>(current);
  auto newPotion =  new Potion(*potion);
  return newPotion;
}

Item* ItemFactory::get_item(Item::ItemType item_type, Item::ItemSubtype item_subtype)
{
  switch(item_type)
  {
    case Item::ItemType::POTION:
      return ItemFactory::get_potion(item_subtype);
    default:
      return nullptr;
  }
}

Item::ItemType ItemFactory::calc_item_type(Monster::MonsterType monster_type, int xp_level)
{
  //TODO: do some logic here
  return Item::ItemType::POTION;
}

Item::ItemSubtype ItemFactory::calc_item_subtype(Item::ItemType item_type, Monster::MonsterType monster_type, int xp_level)
{
  switch(item_type)
  {
    case Item::ItemType::POTION:
      return Item::ItemSubtype::POTION_HEALTH;
  }
}
