#ifndef ITEM_H
#define ITEM_H 

#include <vector>
#include <string>
#include "attribute_modifiers.h"

class Item
{
public:
  enum class ItemType {CORPSE=0, WEAPON, POTION, SCROLL};
  enum class ItemSubtype {
    //CORPSE
    CORPSE_ORC,
    CORPSE_DEVIL,
    //WEAPON
    WEAPON_KRIS,
    //POTION
    POTION_HEALTH
  };
  
  Item (std::string name, ItemType itemType, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  Item(std::string name, ItemType itemType, ItemSubtype subtype);
  virtual ~Item ();
  Item(Item& other);
  
  ItemType item_type();
  ItemSubtype item_subtype();
  
  std::string name();

  virtual int calc_damage(Actor&);
  virtual int max_damage() {return 1;};
  bool interesting();

protected:
  ItemType _item_type;
  ItemSubtype _item_subtype;
  std::vector<AttributeModifiers> _modifiers;
  std::string _name;

};
#endif
