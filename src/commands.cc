#include "commands.h"
#include <SDL2/SDL.h>
#include "world.h"
#include "actor.h"
#include "player.h"
#include "potion.h"

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

bool CommandProcessor::Process(Command command, Actor& actor)
{
  bool result = attempt_process(command, actor);
  if(result)
    actor.use_action_points(command.cost);

  return result;
}

bool CommandProcessor::attempt_process(Command command, Actor& actor)
{
  switch(command.command)
  {
    case Commands::CMD::CMD_MOVE_UP:
      actor.moveUp();
      break;
    case Commands::CMD::CMD_MOVE_DOWN:
      actor.moveDown();
      break;
    case Commands::CMD::CMD_MOVE_LEFT:
      actor.moveLeft();
      break;
    case Commands::CMD::CMD_MOVE_RIGHT:
      actor.moveRight();
      break;
    case Commands::CMD::CMD_EXPLORE:
      return static_cast<Player&>(actor).explore();
      break;
    case Commands::CMD::CMD_MOVE_TO_TILE:
      return actor.move_to_target();
    case Commands::CMD::CMD_USE:
      return use(actor, command.target);
    case Commands::CMD::CMD_DROP:
      return drop(actor, command.target);
    case Commands::CMD::NOP:
      return true;
    default:
      SDL_Log("Missing a command type!");
      break;
  }

  return true;
}

bool CommandProcessor::use(Actor& actor, GameObject* target)
{
  auto item = static_cast<Item*>(target);
  actor.inventory()->use(item, actor);

  return true;
}

bool CommandProcessor::drop(Actor& actor, GameObject* target)
{
  auto item = static_cast<Item*>(target);
  actor.inventory()->drop(item, *actor.tile());
  return true;
}
