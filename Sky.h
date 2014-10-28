#ifndef SKY_H
#define SKY_H

#include "Library.h"
#include "AbstractObject.h"

class Sky: public AbstractObject
{
public:
  Sky(GLfloat size);
  virtual void render();
  
private:
  GLUquadric* quad;
  GLuint textureId;
};

#endif
