#ifndef SCROLL_H
#define SCROLL_H 

#include "item.h"
#include "game_types.h"

class Scroll : Item
{
public:
  Scroll(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  virtual ~Scroll ();

private:
  /* data */
};
#endif
