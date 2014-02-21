#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H 

#include <map>

#include "item.h"
#include "potion.h"


class ItemFactory
{
public:
  static Item* Build();
  static void Init();


private:
  static void init_potions();
  static std::map<Item::ItemType, std::map<Item::ItemSubtype, Item*>> _prototypes;

  static Potion& getProtoPotion(Item::ItemSubtype subtype);
};
#endif
