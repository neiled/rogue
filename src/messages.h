#ifndef MESSAGES_H_
#define MESSAGES_H_ 

#include <deque>
#include <string>

class Messages
{
public:
  static void Add(std::string new_message);
  static bool HasMessages();
  static std::string PopMessage();
  static std::deque<std::string> AllMessages();
  static void Push();
  static void Push(std::string message);
  static void Clear();

private:
  static std::deque<std::string> _messages;
  static std::string _current_message;
};
#endif
