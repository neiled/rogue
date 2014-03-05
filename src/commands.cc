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

bool CommandProcessor::Process(Commands::CMD command, Actor& actor)
{
  switch(command)
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
    default:
      break;
  }

  return true;

}
