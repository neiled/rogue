#ifndef ITEM_H
#define ITEM_H 


class Item
{
public:
  enum class ItemType {ORC_CORPSE=0, WEAPON};
  
  Item (ItemType itemType);
  virtual ~Item ();
  
  ItemType item_type();

private:
  ItemType _item_type;

};
#endif
