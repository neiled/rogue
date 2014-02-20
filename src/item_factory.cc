#include "item_factory.h"
#include "item.h"
#include "potion.h"

Item* ItemFactory::Build()
{
  return new Potion(Item::ItemSubtype::POTION_HEALTH);
}
