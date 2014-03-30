#include "item_factory.h"
#include "item.h"
#include "potion.h"
#include "weapon.h"
#include "scroll.h"
#include "chest.h"
#include "random.h"
#include <SDL2/SDL.h>

std::map<ItemType, std::map<ItemSubtype, Item*>> ItemFactory::_prototypes;
std::map<ItemType, std::map<ItemSubtype, int>> ItemFactory::_weightings;
std::map<ItemType, std::map<ItemSubtype, int>> ItemFactory::_cdf;
std::map<ItemType, int> ItemFactory::_sum_weights;

Item* ItemFactory::Build(int depth)
{
  auto type = ItemFactory::calc_item_type(depth);
  auto subtype = ItemFactory::calc_item_subtype(type, depth);
  return ItemFactory::get_item(type, subtype);
}

Item* ItemFactory::Build(MonsterType monster_type, int xp_level)
{
  auto item_type = ItemFactory::calc_item_type(monster_type, xp_level);
  auto item_subtype = ItemFactory::calc_item_subtype(item_type, xp_level);
  return ItemFactory::get_item(item_type, item_subtype);
}

Item* ItemFactory::Build(ItemType item_type, int xp_level)
{
  auto item_subtype = ItemFactory::calc_item_subtype(item_type, xp_level);  
  return ItemFactory::get_item(item_type, item_subtype);
}

Item* ItemFactory::Build(ItemType item_type, ItemSubtype subtype)
{
  return ItemFactory::get_item(item_type, subtype);
}

void ItemFactory::Init()
{
  ItemFactory::init_potions();
  ItemFactory::init_weapons();
  ItemFactory::init_corpses();
  ItemFactory::init_scrolls();
  ItemFactory::init_other();
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
    new Potion("Small Health Potion", ItemSubtype::POTION_HEALTH_SMALL, {{Actor::Attribute::HEALTH, 25, 0}}),
    7500);
  ItemFactory::add_item(
    new Potion("Health Potion", ItemSubtype::POTION_HEALTH, {{Actor::Attribute::HEALTH, 50, 0}}),
    2500);    
  ItemFactory::add_item(
    new Potion("Large Health Potion", ItemSubtype::POTION_HEALTH_LARGE, {{Actor::Attribute::HEALTH, 100, 0}}),
    1500);    
}

void ItemFactory::init_corpses()
{
  ItemFactory::add_item(
      new Item("Orc Corpse", ItemType::CORPSE, ItemSubtype::CORPSE_ORC),
      0);
  ItemFactory::add_item(
      new Item("Devil Corpse", ItemType::CORPSE, ItemSubtype::CORPSE_DEVIL),
      0);
  ItemFactory::add_item(
      new Item("Skeleton Corpse", ItemType::CORPSE, ItemSubtype::CORPSE_SKELETON),
      0);
}

void ItemFactory::init_weapons()
{
  ItemFactory::add_item(
    new Weapon("Rusted Kris", ItemSubtype::WEAPON_KRIS_RUSTED, 1, 3, {}),
    7500);
  ItemFactory::add_item(
    new Weapon("Low quality Kris", ItemSubtype::WEAPON_KRIS_LOW, 2, 5, {}),
    5000);
  ItemFactory::add_item(
    new Weapon("Kris", ItemSubtype::WEAPON_KRIS, 3, 6, {}),
    1000);    
  ItemFactory::add_item(
    new Weapon("Good Quality Kris", ItemSubtype::WEAPON_KRIS_GOOD, 5, 10, {}),
    250);    

}

void ItemFactory::init_scrolls()
{
  ItemFactory::add_item(
      new Scroll("Blink Scroll", ItemSubtype::SCROLL_BLINK, {}),
      100);
  ItemFactory::add_item(
      new Scroll("Reveal Scroll", ItemSubtype::SCROLL_REVEAL, {}),
      50);      
}

void ItemFactory::init_other()
{
  ItemFactory::add_item(
      new Chest(),
      0);
}
void ItemFactory::add_item(Item* item, int weighting)
{
  ItemFactory::_prototypes[item->item_type()][item->item_subtype()] = item;
  ItemFactory::_weightings[item->item_type()][item->item_subtype()] = weighting;
}

Potion* ItemFactory::get_potion(ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[ItemType::POTION][subtype];
  auto potion =  static_cast<Potion*>(current);
  auto newPotion =  new Potion(*potion);
  return newPotion;
}

Weapon* ItemFactory::get_weapon(ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[ItemType::WEAPON][subtype];
  auto weapon = static_cast<Weapon*>(current);
  auto newWeapon = new Weapon(*weapon);
  return newWeapon;
}

Scroll* ItemFactory::get_scroll(ItemSubtype subtype)
{
  auto current = ItemFactory::_prototypes[ItemType::SCROLL][subtype];
  auto scroll = static_cast<Scroll*>(current);
  auto newScroll = new Scroll(*scroll);
  return newScroll;
}

Item* ItemFactory::get_item(ItemType item_type, ItemSubtype item_subtype)
{
  switch(item_type)
  {
    case ItemType::POTION:
      return ItemFactory::get_potion(item_subtype);
    case ItemType::WEAPON:
      return ItemFactory::get_weapon(item_subtype);
    case ItemType::SCROLL:
      return ItemFactory::get_scroll(item_subtype);
    case ItemType::CORPSE:
      return new Item(*ItemFactory::_prototypes[item_type][item_subtype]);
    case ItemType::CHEST:
      return new Chest(*static_cast<Chest*>(ItemFactory::_prototypes[item_type][item_subtype]));
    default:
      SDL_Log("You need to add this type of item...");
      return nullptr;
  }
}

ItemType ItemFactory::calc_item_type(MonsterType monster_type, int xp_level)
{
  int random = Random::Between(0,100);



  if(random < 50)
    return ItemType::POTION;
  else if(random < 90)
    return ItemType::WEAPON;
  else
    return ItemType::SCROLL;
}

ItemType ItemFactory::calc_item_type(int depth)
{
  int random = Random::Between(0,100);

  if(random < 50)
    return ItemType::POTION;
  else if(random < 90)
    return ItemType::WEAPON;
  else
    return ItemType::SCROLL;
}

ItemSubtype ItemFactory::calc_item_subtype(ItemType item_type, int xp_level)
{
  int max_random_number = _sum_weights[item_type];
  int random_number = Random::Between(0,max_random_number);
  
  auto weightings = _cdf[item_type];
  
  for(auto current_weighting : weightings)
  {
    if(random_number <= current_weighting.second)
      return current_weighting.first;
  }

  SDL_Log("Something wrong with the CDF as should never see this!");
  return ItemSubtype::CORPSE_DEVIL;
}

std::vector<AttributeModifiers> ItemFactory::generate_magic_modifiers(int level)
{
  if(level <= 2)
    return {};

  return {};



}
