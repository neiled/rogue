#ifndef GAME_TYPES_H
#define GAME_TYPES_H 

#include <map>

class DirectionalSprite;
class Sprite;


enum class MonsterType {Orc, Devil};
enum class MonsterState {Asleep, Awake, Hunting, Wandering};

enum class ItemType {CORPSE=0, WEAPON, POTION, SCROLL};
enum class ItemSubtype {
  //CORPSE
  CORPSE_ORC,
  CORPSE_DEVIL,
  //WEAPON
  WEAPON_KRIS_RUSTED,
  WEAPON_KRIS_SMALL,
  //POTION
  POTION_HEALTH_SMALL,
  POTION_HEALTH_LARGE
};

enum struct TileType {Floor = 0, Rock, StairsDown, StairsUp, Door};

typedef std::map<MonsterType, DirectionalSprite*> monster_sprites_t;
typedef std::map<ItemType, std::map<ItemSubtype, Sprite*>> item_sprites_t;
typedef std::map<TileType, Sprite*> level_sprites_t;
enum class GameState {MENU_START, GAME, MENU_INVENTORY, DEAD, STARTING, STOP};

#endif
