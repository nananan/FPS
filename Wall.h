#ifndef WALL_H
#define WALL_H

#include "Library.h"
#include "Scacchiera.h"
#include "AbstractObject.h"

#define heig 4.0

class Wall: public AbstractObject
{
public:
  Wall (float x, float y, float z, int dir, int dim);
  virtual void render();
  int getDim();
  int getDir();
  
private:
  float x;
  float y;
  float z;
  int dir;
  int dim;
  GLuint textureId;
};

#endif
