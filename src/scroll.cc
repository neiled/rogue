#include "scroll.h"
#include "level.h"
#include "messages.h"

Scroll::Scroll(std::string name, ItemSubtype subtype, std::vector<AttributeModifiers> modifiers) : Item(name, ItemType::SCROLL, subtype, modifiers)
{
}

Scroll::~Scroll()
{
}

void Scroll::cast(Actor& owner, Actor* target)
{
  switch(_item_subtype)
  {
    case ItemSubtype::SCROLL_BLINK:
      blink(owner);
      break;
    case ItemSubtype::SCROLL_REVEAL:
      reveal(owner);
      break;
  }
}

void Scroll::blink(Actor& owner)
{
  auto newTile = owner.level().getRandomTileOfType(TileType::Floor);
  if(newTile->actor())
  {
    Messages::PushBad("Blink failed.");
  }
  else
  {
    owner.set_tile(*newTile);
    Messages::PushGood("You open your eyes in a new area.");
  }

}

void Scroll::reveal(Actor& owner)
{
  owner.level()->reveal();
  Messages::PushGood("You gain knowledge of the current area.");
}
