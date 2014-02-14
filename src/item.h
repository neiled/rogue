#ifndef ITEM_H
#define ITEM_H 


class Item
{
public:
  enum class ItemType {WEAPON};
  
  Item (ItemType itemType);
  virtual ~Item ();
  
  ItemType item_type();

private:
  ItemType _item_type;

};
#endif
