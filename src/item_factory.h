#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H 

#include <map>

#include "game_types.h"
#include "attribute_modifiers.h"

class Potion;
class Weapon;
class Wand;
class Scroll;
class Item;

class ItemFactory
{
public:
  static Item* Build(int depth);
  static Item* Build(MonsterType monster_type, int xp_level);
  static Item* Build(ItemType item_type, int xp_level);
  static Item* Build(ItemType item_type, ItemSubtype, int level);
  static void Init();


private:
  static void init_potions();
  static void init_weapons();
  static void init_wands();
  static void init_corpses();
  static void init_scrolls();
  static void init_other();
  static void calc_cdf();
  
  static Item* get_item(ItemType, ItemSubtype, int level);
  static ItemType calc_item_type(MonsterType monster_type, int xp_level);
  static ItemType calc_item_type(int xp_level);
  static ItemSubtype calc_item_subtype(ItemType item_type, int xp_level);
  static std::map<ItemType, std::map<ItemSubtype, Item*>> _prototypes;
  static std::map<ItemType, std::map<ItemSubtype, int>> _weightings;
  static std::map<ItemType, std::map<ItemSubtype, int>> _cdf;
  static std::map<ItemType, int> _sum_weights;
  static void add_item(Item* item, int weighting);

  static Potion* get_potion(ItemSubtype subtype, int level);
  static Weapon* get_weapon(ItemSubtype subtype, int level);
  static Wand* get_wand(ItemSubtype subtype, int level);
  static Scroll* get_scroll(ItemSubtype subtype, int level);

  static std::vector<AttributeModifiers> generate_magic_modifiers(int level);
};
#endif
