#include <vector>
#include "render_monsters.h"
#include "level.h"
#include "directional_sprite.h"
#include "renderer.h"
#include "monster.h"

void RenderMonsters::Render(Renderer& renderer, monster_sprites_t monster_sprites, Level& level)
{
  std::vector<Monster*> monsters = level.getMonsters();
  for(Monster* m : monsters)
  {
    if(m->dead())
      continue;
    auto currentTile = m->tile();
    auto lit = level.light_map(currentTile->x(), currentTile->y());
    if(lit != Level::LightType::Lit)
      continue;
    auto sprite = monster_sprites[m->monster_type()];
    sprite->update(m->direction);
    renderer.draw_sprite(sprite, *currentTile);
    renderer.draw_health(*m);
    //TODO: If monster == player.target_monster() render a border
  }
}
