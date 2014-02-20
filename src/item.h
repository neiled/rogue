#ifndef ITEM_H
#define ITEM_H 


class Item
{
public:
  enum class ItemType {CORPSE=0, WEAPON, POTION};
  enum class ItemSubtype {
    CORPSE_ORC,
    WEAPON_KNIFE,
    POTION_HEALTH
  };
  
  Item (ItemType itemType, ItemSubtype subtype);
  virtual ~Item ();
  
  ItemType item_type();
  ItemSubtype item_subtype();

private:
  ItemType _item_type;
  ItemSubtype _item_subtype;

};
#endif
