#ifndef LEVELBUILDER_H_
#define LEVELBUILDER_H_

#include "levelbuilder.h"
#include "level.h"

class LevelBuilder
{
  public:
    LevelBuilder ();
    virtual ~LevelBuilder ();
    void buildLevel(Level* level);

  private:
    /* data */
};

#endif
