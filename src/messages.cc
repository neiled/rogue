#include "messages.h"
#include <SDL2/SDL.h>

std::deque<std::string> Messages::_messages;
std::string Messages::_current_message = "";

void Messages::Add(std::string new_message)
{
  Messages::_current_message += " " + new_message +".";
  SDL_Log(new_message.c_str());
}

void Messages::Push()
{
  if(_current_message.length() > 0)
  {
    Messages::_messages.push_back(_current_message);
    _current_message = "";
  }
}

void Messages::Push(std::string message)
{
    Messages::_messages.push_back(message);
}

void Messages::Clear()
{
  Messages::_messages.clear();
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
