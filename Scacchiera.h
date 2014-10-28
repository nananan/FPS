#ifndef SCACCHIERA_H
#define SCACCHIERA_H

#include "AbstractObject.h"

class Scacchiera: public AbstractObject
{
public:
  Scacchiera();
  virtual void render();
  
  float getDim();
  
private:
  float dim;
  GLuint textureId;
};

#endif
