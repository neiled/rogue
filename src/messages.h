#ifndef MESSAGES_H_
#define MESSAGES_H_ 

#include <deque>
#include <string>
#include <vector>
#include "game_types.h"

struct Message
{
  MessageType message_type;
  std::string message;
};

class Messages
{
public:
  static void Add(std::string new_message);
  static void AddBad(std::string new_message);
  static void AddGood(std::string new_message);
  static bool HasMessages();
  static std::vector<Message> PopMessage();
  static std::deque<std::vector<Message>> AllMessages();
  static void Push();
  static void Push(std::string message);
  static void PushBad(std::string message);
  static void PushGood(std::string message);
  static void Clear();

private:
  static void add_message(MessageType type, std::string message);
  static void push_message(MessageType type, std::string message);
  static std::deque<std::vector<Message>> _messages;
  static std::vector<Message> _current_messages;
  //static std::string _current_message;
};
#endif
