#ifndef FINISHINGLINE_H
#define FINISHINGLINE_H

#include "Library.h"
#include "AbstractObject.h"

class FinishingLine: public AbstractObject
{
public:
  FinishingLine(GLfloat positionX, GLfloat positionY, GLfloat positionZ);
  virtual void render();
  GLfloat getRadius();
  
  bool collisionLine(float forwardX, float xPlayer, float forwardY, float yPlayer);
  
private:
  GLfloat radius;
  GLUquadric* quad;
  GLuint textureId;
  
  int rotate = 0;
};

#endif
