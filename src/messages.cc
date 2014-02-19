#include "messages.h"
#include <SDL2/SDL.h>

std::deque<std::string> Messages::_messages;

void Messages::Add(std::string new_message)
{
  Messages::_messages.push_back(new_message);
}

bool Messages::HasMessages()
{
  return Messages::_messages.empty() == false;
}

std::string Messages::PopMessage()
{
  std::string msg = _messages.front();
  _messages.pop_front();
  return msg;
}

std::deque<std::string> Messages::AllMessages()
{
  return _messages;
}
