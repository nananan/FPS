#ifndef LINECOLLISION_H
#define LINECOLLISION_H

#include "Player.h"
#include "Camera.h"
#include "Library.h"
#include "AbstractObject.h"

class LineCollision: public AbstractObject
{
public:
  LineCollision(Player* player, Camera* camera);
  virtual void render();
  
private:
  Player* player;
  Camera* camera;
};

#endif
