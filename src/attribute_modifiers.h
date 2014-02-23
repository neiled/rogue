#ifndef ATTRIBUTE_MODIFIERS_H
#define ATTRIBUTE_MODIFIERS_H

#include "actor.h"

class AttributeModifiers
{
public:
  AttributeModifiers (Actor::Attribute attr, int modifier, int turns);
  virtual ~AttributeModifiers ();
  void apply(Actor& actor);

  Actor::Attribute attr();
  int modifier();
  int turns();

private:
  Actor::Attribute _attr;
  int _modifier;
  int _turns;
};
#endif
