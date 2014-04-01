#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H 

#include <string>

class GameObject
{
  public:
    GameObject(std::string name);
    GameObject(GameObject&);
    virtual std::string name();

  protected:
    std::string _name;

};
#endif
