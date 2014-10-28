#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include "Library.h"

struct ObjectSize
{
    GLfloat width;
    GLfloat height;
    GLfloat depth;

    ObjectSize()
    {
        this->width = 0;
        this->height = 0;
        this->depth = 0;
    }
    
    void setHeight(GLfloat h)
    {
      height = h;
    }
    
};

class AbstractObject 
{
public:
  AbstractObject();
  virtual void render() = 0;
  virtual void setPosition(float x, float y, float z);
  virtual ObjectSize getSize();
  virtual void setSize (GLfloat width, GLfloat height, GLfloat depth);
  
  float getX();
  float getY();
  float getZ();
  
protected:
  GLuint loadTexture(const char* imagePath);
  
private:
  float x;
  float y;
  float z;
  ObjectSize size;
};

#endif
