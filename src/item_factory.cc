#include "item_factory.h"
#include "item.h"
#include "potion.h"
#include "weapon.h"
#include "random.h"
#include <SDL2/SDL.h>

std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> ItemFactory::_prototypes;
std::map<Item::ItemType, std::map<Item::ItemSubtype, int>> ItemFactory::_weightings;
std::map<Item::ItemType, std::map<Item::ItemSubtype, int>> ItemFactory::_cdf;
std::map<Item::ItemType, int> ItemFactory::_sum_weights;

Item* ItemFactory::Build(int depth)
{
  auto type = ItemFactory::calc_item_type(depth);
  auto subtype = ItemFactory::calc_item_subtype(type, depth);
  return ItemFactory::get_item(type, subtype);
}

Item* ItemFactory::Build(Monster::MonsterType monster_type, int xp_level)
{
  auto item_type = ItemFactory::calc_item_type(monster_type, xp_level);
  auto item_subtype = ItemFactory::calc_item_subtype(item_type, xp_level);
  return ItemFactory::get_item(item_type, item_subtype);
}

Item* ItemFactory::Build(Item::ItemType item_type, int xp_level)
{
  auto item_subtype = ItemFactory::calc_item_subtype(item_type, xp_level);  
  return ItemFactory::get_item(item_type, item_subtype);
}

void ItemFactory::Init()
{
  ItemFactory::init_potions();
  ItemFactory::init_weapons();
  ItemFactory::calc_cdf();
}

void ItemFactory::calc_cdf()
{
  for(auto types : _weightings)
  {
    int sum = 0;
    for(auto subtypes : _weightings[types.first])
    {
      sum += subtypes.second;
      _cdf[types.first][subtypes.first] = sum;
    }
    _sum_weights[types.first] = sum;
  }
}

void ItemFactory::init_potions()
{
  ItemFactory::add_item(
    new Potion("Small Health Potion", Item::ItemSubtype::POTION_HEALTH, {{Actor::Attribute::HEALTH, 25, 0}}),
    7500);
  ItemFactory::add_item(
    new Potion("Large Health Potion", Item::ItemSubtype::POTION_HEALTH, {{Actor::Attribute::HEALTH, 50, 0}}),
    2500);    
}

void ItemFactory::init_weapons()
{
  ItemFactory::add_item(
    new Weapon("Small Kris", Item::ItemSubtype::WEAPON_KRIS, 5, {}),
    7500);

}
void ItemFactory::add_item(Item* item, int weighting)
{
  ItemFactory::_prototypes[item->item_type()][item->item_subtype()] = item;
  ItemFactory::_weightings[item->item_type()][item->item_subtype()] = weighting;
}

Potion* ItemFactory::get_potion(Item::ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[Item::ItemType::POTION][subtype];
  auto potion =  static_cast<Potion*>(current);
  auto newPotion =  new Potion(*potion);
  return newPotion;
}

Weapon* ItemFactory::get_weapon(Item::ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[Item::ItemType::WEAPON][subtype];
  auto weapon = static_cast<Weapon*>(current);
  auto newWeapon = new Weapon(*weapon);
  return newWeapon;
}

Item* ItemFactory::get_item(Item::ItemType item_type, Item::ItemSubtype item_subtype)
{
  switch(item_type)
  {
    case Item::ItemType::POTION:
      return ItemFactory::get_potion(item_subtype);
    case Item::ItemType::WEAPON:
      return ItemFactory::get_weapon(item_subtype);
    default:
      SDL_Log("You need to add this type of item...");
      return nullptr;
  }
}

Item::ItemType ItemFactory::calc_item_type(Monster::MonsterType monster_type, int xp_level)
{
  int random = Random::Between(0,100);

  if(random < 50)
    return Item::ItemType::POTION;
  return Item::ItemType::WEAPON;
}

Item::ItemType ItemFactory::calc_item_type(int depth)
{
  int random = Random::Between(0,100);

  if(random < 50)
    return Item::ItemType::POTION;
  return Item::ItemType::WEAPON;

}

Item::ItemSubtype ItemFactory::calc_item_subtype(Item::ItemType item_type, int xp_level)
{
  int max_random_number = _sum_weights[item_type];
  int random_number = Random::Between(0,max_random_number);
  
  auto weightings = _weightings[item_type];
  
  for(auto current_weighting : weightings)
  {
    if(random_number <= current_weighting.second)
      return current_weighting.first;
  }

  SDL_Log("Something wrong with the CDF as should never see this!");
}
