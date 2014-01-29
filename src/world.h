#ifndef WORLD_H_
#define WORLD_H_

class World
{
public:
  World ();
  virtual ~World ();
  void update();
  Player* getPlayer();

private:
  /* data */
};
#endif
