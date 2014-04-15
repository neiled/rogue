#include "wand.h"
#include <SDL2/SDL.h>
#include "tile.h"
#include "messages.h"
#include "random.h"

Wand::Wand(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers, int range) : RangedWeapon(name, ItemType::WAND, subtype, min_damage(subtype), max_damage(subtype), modifiers, range), _charges(10)
{
}

Wand::Wand(Wand& other) : RangedWeapon(other)
{
  _charges = other._charges;
}

Wand::~Wand()
{}

void Wand::fire(Actor& owner, Tile& tile)
{
  switch(_item_subtype)
  {
    case ItemSubtype::WAND_FLAME:
      flame(owner, tile);
      break;
    default:
      SDL_Log("Missing a wand type");
      break;
  }
}

int Wand::min_damage(ItemSubtype type)
{
  switch(type)
  {
    case ItemSubtype::WAND_FLAME:
      return 5;
    default:
      SDL_Log("Need to add this wand type to min_damage");
      return 0;
  }
}

int Wand::max_damage(ItemSubtype type)
{
  switch(type)
  {
    case ItemSubtype::WAND_FLAME:
      return 15;
    default:
      SDL_Log("Need to add this wand type to max_damage");
      return 0;
  }
}

void Wand::flame(Actor& owner, Tile& tile)
{
  if(_charges <= 0)
  {
    Messages::PushBad("There are no charges remaining on this wand.");
    return;
  }

  if(owner.tile()->distance_to(tile) > _range)
  {
    Messages::PushBad("Target is out of range!");
    return;
  }

  if(!tile.actor())
  {
    Messages::PushBad("Nobody there to target.");
    return;
  }

  auto other = tile.actor();
  if(&owner == other)
  {
    Messages::PushBad("Can't target yourself.");
    return;
  }

  int damage = Random::BetweenNormal(_min_damage, _max_damage);

  other->takeDamage(damage, &owner);
  Messages::PushGood("You damage the " + other->name() + " for " + std::to_string(damage) + " damage with your wand");
  _charges--;
}
