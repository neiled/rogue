#include "game_object.h"

GameObject::GameObject(std::string name) : _name(name)
{}

GameObject::GameObject(GameObject& other)
{
  _name = other.name();
}

std::string GameObject::name()
{
  return _name;
}
