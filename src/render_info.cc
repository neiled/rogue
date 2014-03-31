#include "render_info.h"
#include "renderer.h"
#include "player.h"
#include "item.h"
#include "game.h"
#include "sprite.h"
#include "level.h"
#include "weapon.h"



RenderInfo::RenderInfo(Graphics* g): _graphics(g)
{
}

void RenderInfo::init()
{
  _info_char = new Sprite(_graphics, "./content/outline.png", 0, 0, 150, 271);
}

void RenderInfo::render(Renderer& renderer, Game& game, item_sprites_t items, SDL_Rect vp_info)
{
  SDL_RenderSetViewport(_graphics->Renderer, &vp_info);
  render_player_info(renderer, game, *game.player(), items);
  if(game.state() == GameState::GAME)
    render_actor_info(renderer, game, game.player()->target_actor(), 550);
  else if(game.state() == GameState::LOOK)
    render_look(renderer, game, *game.player(), 550);
}

void RenderInfo::render_look(Renderer& renderer, Game& game, Player& player, int start_y)
{
  Tile* look_tile = player.level().look_tile();
  if(!look_tile)
    return;
  if(player.can_see_tile(*player.level().look_tile()) == false)
    return;

  int string_y = start_y;
  int string_gap = 25;

  if(look_tile->items().size() > 0)
  {
    render_string(renderer, "Items", string_y);
    string_y += string_gap;
    for(auto item : look_tile->items())
    {
      render_string(renderer, item->name(), string_y);
      string_y += string_gap;
    }
  }
  if(look_tile->actor())
  {
    auto actor = look_tile->actor();
    if(actor->is_player())
      return;
    if(actor->dead())
      return;

    render_actor_info(renderer, game, actor, string_y);
  }

  
}

void RenderInfo::render_player_info(Renderer& renderer, Game& game, Player& player, item_sprites_t items)
{
  _info_char->draw(25, 0, 0, 0);
  int string_y = 360;
  int string_gap = 25;
  if(player.weapon())
  {
    auto item = items[player.weapon()->item_type()][player.weapon()->item_subtype()];
    item->draw(140, 125, 0, 0, SDL_ALPHA_OPAQUE);
    auto weapon = static_cast<Weapon*>(player.weapon());
    render_string(renderer, "Dmg:  " + weapon->damage_name() , string_y);
  }
  renderer.draw_health_bar(25, 300, 150, 20, player.health(), player.max_health(), player.previous_health());

  renderer.draw_xp_bar(25, 330, 150, 20, player.xp() - player.min_xp(), player.max_xp());

  string_y += string_gap;
  render_string(renderer, "Lvl:  " + std::to_string(player.xp_level()), string_y);
  string_y += string_gap;
  render_string(renderer, "Atk:  " + std::to_string(player.atk()), string_y);
  string_y += string_gap;
  render_string(renderer, "Def:  " + std::to_string(player.def()), string_y);
  string_y += string_gap;
  render_string(renderer, "Dpth: " + std::to_string(player.level().depth()), string_y);
  string_y += string_gap;
  render_string(renderer, "Turn: " + std::to_string(game.turn()), string_y);  
}

void RenderInfo::render_string(Renderer& renderer, std::string message, int y)
{
  renderer.render_string(message, 10, y, 16);
}

void RenderInfo::render_actor_info(Renderer& renderer, Game& game, Actor* actor, int start_y)
{
  if(!actor)
    return;
  if(actor->dead())
    return;
  int string_y = start_y;
  int string_gap = 25;
  
  render_string(renderer, "Name: " + actor->name(), string_y);
  string_y += string_gap;  
  
  renderer.draw_health_bar(25, string_y, 150, 20, actor->health(), actor->max_health(), actor->previous_health());
  string_y += string_gap;
  render_string(renderer, "Dmg: " +
        std::to_string(actor->min_damage(*game.player())) +
        "-" +
        std::to_string(actor->max_damage(*game.player())), string_y);
  string_y += string_gap;
  render_string(renderer, "Lvl: " + std::to_string(actor->xp_level()), string_y);
  string_y += string_gap;
  render_string(renderer, "Atk: " + std::to_string(actor->atk()), string_y);
  string_y += string_gap;
  render_string(renderer, "Def: " + std::to_string(actor->def()), string_y);

}

