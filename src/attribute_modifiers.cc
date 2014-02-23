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

Actor::Attribute AttributeModifiers::attr()
{
  return _attr;
}

int AttributeModifiers::turns()
{
  return _turns;
}

int AttributeModifiers::modifier()
{
  return _modifier;
}
