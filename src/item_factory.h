#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H 

#include <map>

#include "item.h"
#include "potion.h"
#include "weapon.h"
#include "monster.h"


class ItemFactory
{
public:
  static Item* Build(int depth);
  static Item* Build(Monster::MonsterType monster_type, int xp_level);
  static Item* Build(Item::ItemType item_type, int xp_level);
  static void Init();


private:
  static void init_potions();
  static void init_weapons();
  static void calc_cdf();
  
  static Item* get_item(Item::ItemType, Item::ItemSubtype);
  static Item::ItemType calc_item_type(Monster::MonsterType monster_type, int xp_level);
  static Item::ItemType calc_item_type(int xp_level);
  static Item::ItemSubtype calc_item_subtype(Item::ItemType item_type, int xp_level);
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> _prototypes;
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, int>> _weightings;
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, int>> _cdf;
  static std::map<Item::ItemType, int> _sum_weights;
  static void add_item(Item* item, int weighting);

  static Potion* get_potion(Item::ItemSubtype subtype);
  static Weapon* get_weapon(Item::ItemSubtype subtype);
};
#endif
