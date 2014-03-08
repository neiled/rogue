#ifndef SCROLL_H
#define SCROLL_H 

#include "item.h"
#include "game_types.h"

class Scroll : public Item
{
public:
  Scroll(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers);
  virtual ~Scroll ();
  void cast(Actor& owner, Actor* target);

private:
  void blink(Actor& owner);
};
#endif
