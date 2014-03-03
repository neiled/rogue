#ifndef SCROLL_H
#define SCROLL_H 

#include "item.h"

class Scroll : Item
{
public:
  Scroll(std::string name, Item::ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  virtual ~Scroll ();

private:
  /* data */
};
#endif
