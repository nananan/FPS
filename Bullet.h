#ifndef BULLET_H
#define BULLET_H

#include "Enemy.h"
#include "Camera.h"
#include "Player.h"
#include "Library.h"
#include "AbstractObject.h"

#define veloc 1

class Bullet: public AbstractObject
{
public:
  Bullet(Player* player, Camera* camera);
  virtual void render();
  bool collision(Enemy* enemy, vector<Wall*> wall);
  void move();
  
private:
  GLUquadric* quad;
  Player* player;
  Camera* camera;
  
  float angolo;
};

#endif
