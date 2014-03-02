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
  static void Clear();

private:
  static std::deque<std::string> _messages;
};
#endif
