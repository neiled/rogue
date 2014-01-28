#ifndef LEVELBUILDER_H_
#define LEVELBUILDER_H_

#include "levelbuilder.h"

class Level;

class LevelBuilder
{
  public:
    LevelBuilder ();
    virtual ~LevelBuilder ();
    void BuildLevel(Level* level);

  private:
    /* data */
};

#endif
