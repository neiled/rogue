#ifndef COMMANDS_H
#define COMMANDS_H 

class Actor;
class World;

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
                  CMD_EXPLORE };
};

class CommandProcessor
{
public:
  CommandProcessor ();
  virtual ~CommandProcessor ();
  void Process(Commands::CMD command, Actor& actor);

private:
  
};
#endif
