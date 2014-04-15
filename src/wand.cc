#include "wand.h"
#include <SDL2/SDL.h>
#include "tile.h"
#include "messages.h"

Wand::Wand(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers, int range) : RangedWeapon(name, ItemType::WAND, subtype, 0, 0, modifiers, range), _charges(10)
{
}

Wand::Wand(Wand& other) : RangedWeapon(other)
{
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

  if(&owner == tile.actor())
  {
    Messages::PushBad("Can't target yourself.");
    return;
  }

  tile.actor()->takeDamage(15, &owner);
  Messages::PushGood("You damage the " + tile.actor()->name() + " for 15 damage with your wand");
  _charges--;
}
