#include "attribute_modifiers.h"

AttributeModifiers::AttributeModifiers(Actor::Attribute attr, int modifier, int turns)
{
  _attr = attr;
  _modifier = modifier;
  _turns = turns;
}

AttributeModifiers::~AttributeModifiers()
{
}
