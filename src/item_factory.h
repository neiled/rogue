#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H 

#include <map>

#include "item.h"
#include "potion.h"
#include "monster.h"


class ItemFactory
{
public:
  static Item* Build();
  static Item* Build(Monster::MonsterType monster_type, int xp_level);
  static void Init();


private:
  static void init_potions();
  static Item* get_item(Item::ItemType, Item::ItemSubtype);
  static Item::ItemType calc_item_type(Monster::MonsterType monster_type, int xp_level);
  static Item::ItemSubtype calc_item_subtype(Item::ItemType item_type, Monster::MonsterType monster_type, int xp_level);
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> _prototypes;
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, int>> _weightings;
  static void add_item(Item* item, int weighting);

  static Potion* get_potion(Item::ItemSubtype subtype);
};
#endif
