#ifndef GAME_TYPES_H
#define GAME_TYPES_H 

#include <map>
#include <vector>

class DirectionalSprite;
class Sprite;


enum class MonsterType {
  Orc,
  Devil,
  Skeleton
};
enum class MonsterState {Asleep, Awake, Hunting, Wandering};

enum class ItemType {
  CORPSE=0,
  WEAPON,
  RANGED,
  WAND,
  POTION,
  SCROLL,
  CHEST
};
enum class ItemSubtype {
  //CORPSE
  CORPSE_ORC,
  CORPSE_DEVIL,
  CORPSE_SKELETON,
  //WEAPON
  WEAPON_KRIS_RUSTED,
  WEAPON_KRIS_LOW,
  WEAPON_KRIS,
  WEAPON_KRIS_GOOD,
  //POTION
  POTION_HEALTH_SMALL,
  POTION_HEALTH,
  POTION_HEALTH_LARGE,
  //SCROLL
  SCROLL_BLINK,
  SCROLL_REVEAL,
  //CHEST
  CHEST,
  //RANGED
  //WAND
  WAND_FLAME
};

enum struct TileType {Floor = 0, Rock, StairsDown, StairsUp, Door};

enum class MessageType {Normal, Good, Bad};

typedef std::map<MonsterType, DirectionalSprite*> monster_sprites_t;
typedef std::map<ItemType, std::map<ItemSubtype, Sprite*>> item_sprites_t;
typedef std::map<TileType, std::vector<Sprite*>> level_sprites_t;

enum class GameState {
  MENU_START,
  MENU_CHEST,
  MENU_INVENTORY,
  GAME, 
  DEAD,
  STARTING,
  STOP,
  LOOK
};

#endif
