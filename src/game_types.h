#ifndef GAME_TYPES_H
#define GAME_TYPES_H 

#include <map>
#include "monster.h"
#include "item.h"

class DirectionalSprite;
class Sprite;


typedef std::map<Monster::MonsterType, DirectionalSprite*> monster_sprites_t;
typedef std::map<Item::ItemType, std::map<Item::ItemSubtype, Sprite*>> item_sprites_t;
enum class GameState {MENU_START, GAME, MENU_INVENTORY, DEAD, STARTING, STOP};

#endif
