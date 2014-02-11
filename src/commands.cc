#include "commands.h"
#include "world.h"
#include "player.h"

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

void CommandProcessor::Process(Commands::CMD command, World* world)
{
  Player* player = world->getPlayer();
  switch(command)
  {
    case Commands::CMD::CMD_MOVE_UP:
      player->moveUp();
      break;
    case Commands::CMD::CMD_MOVE_DOWN:
      player->moveDown();
      break;
    case Commands::CMD::CMD_MOVE_LEFT:
      player->moveLeft();
      break;
    case Commands::CMD::CMD_MOVE_RIGHT:
      player->moveRight();
      break;
    case Commands::CMD::CMD_EXPLORE:
      player->explore();
      break;
    default:
      break;
  }

}
