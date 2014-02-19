#ifndef ITEM_H
#define ITEM_H 


class Item
{
public:
  enum class ItemType {ORC_CORPSE=0, WEAPON_KNIFE, WEAPON_SWORD, WEAPON_CLUB, WEAPON_AXE, POTION};
  
  Item (ItemType itemType);
  virtual ~Item ();
  
  ItemType item_type();

private:
  ItemType _item_type;

};
#endif
