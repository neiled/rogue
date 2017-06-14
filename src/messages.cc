#include "messages.h"

std::deque<std::vector<Message>> Messages::_messages;
std::vector<Message> Messages::_current_messages;
//std::string Messages::_current_message = "";

void Messages::Add(std::string new_message)
{
  add_message(MessageType::Normal, new_message);
}

void Messages::AddBad(std::string new_message)
{
  add_message(MessageType::Bad, new_message);
}

void Messages::AddGood(std::string new_message)
{
  add_message(MessageType::Good, new_message);
}

void Messages::add_message(MessageType type, std::string message)
{
  auto newMessage = Message{type, message + ". "};
  _current_messages.push_back(newMessage);
  SDL_Log(message.c_str());
}

void Messages::Push()
{
  if(_current_messages.empty())
    return;
  _messages.push_back(_current_messages);
  _current_messages = std::vector<Message>();
}

void Messages::Push(std::string message)
{
  push_message(MessageType::Normal, message);
}

void Messages::PushGood(std::string message)
{
  push_message(MessageType::Good, message);
}

void Messages::PushBad(std::string message)
{
  push_message(MessageType::Bad, message);
}

void Messages::push_message(MessageType type, std::string message)
{
  _current_messages.push_back(Message{type, message});
  _messages.push_back(_current_messages);
  _current_messages = std::vector<Message>();
}

void Messages::Clear()
{
  Messages::_messages.clear();
}

bool Messages::HasMessages()
{
  return Messages::_messages.empty() == false;
}

std::vector<Message> Messages::PopMessage()
{
  auto msg = _messages.front();
  _messages.pop_front();
  return msg;
}

std::deque<std::vector<Message>> Messages::AllMessages()
{
  return _messages;
}
