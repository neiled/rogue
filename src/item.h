#ifndef ITEM_H
#define ITEM_H 

#include <vector>
#include <string>
#include "attribute_modifiers.h"
#include "game_types.h"
#include "game_object.h"

class Item : public GameObject
{
public:
  
  Item (std::string name, ItemType itemType, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  Item(std::string name, ItemType itemType, ItemSubtype subtype);
  virtual ~Item ();
  Item(Item& other);
  
  ItemType item_type();
  ItemSubtype item_subtype();

  virtual int max_damage() {return 1;};
  virtual int min_damage() {return 1;};
  virtual bool interesting();
  virtual bool can_pick_up();

  std::vector<AttributeModifiers> modifiers();
  void modifiers(std::vector<AttributeModifiers>);

protected:
  ItemType _item_type;
  ItemSubtype _item_subtype;
  std::vector<AttributeModifiers> _modifiers;

};
#endif
