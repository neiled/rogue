#include "commands.h"
#include "world.h"
#include "actor.h"
#include "player.h"

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

bool CommandProcessor::Process(Command command, Actor& actor)
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
    default:
      break;
  }

  return true;

}
