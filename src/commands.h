#ifndef COMMANDS_H
#define COMMANDS_H 


class Actor;
class World;
class GameObject;

struct Commands
{
  enum class CMD {
                  NOP,
                  CMD_MOVE_UP,
                  CMD_MOVE_UP_RIGHT,
                  CMD_MOVE_RIGHT,
                  CMD_MOVE_DOWN_RIGHT,
                  CMD_MOVE_DOWN,
                  CMD_MOVE_DOWN_LEFT,
                  CMD_MOVE_LEFT,
                  CMD_MOVE_UP_LEFT,
                  CMD_EXPLORE,
                  CMD_MOVE_TO_TILE,
                  CMD_USE,
                  CMD_DROP};
};

struct Command
{
  Commands::CMD command;
  GameObject* target;
  int cost;

  Command(Commands::CMD cmd, GameObject* tgt, int c) : command(cmd), target(tgt), cost(c) {}
  Command(Commands::CMD cmd, GameObject* tgt) : Command(cmd, tgt, 100) {}
  Command(Commands::CMD cmd) : Command(cmd, nullptr) {}
};

class CommandProcessor
{
public:
  CommandProcessor ();
  virtual ~CommandProcessor ();
  bool Process(Command command, Actor& actor);

private:
  bool use(Actor& actor, GameObject* target);
  bool drop(Actor& actor, GameObject* target);
  bool attempt_process(Command command, Actor& actor);
  
};
#endif
