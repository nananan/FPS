#include "AbstractObject.h"

AbstractObject::AbstractObject()
{
  setPosition(0.0, 0.0, 0.0);
}

void AbstractObject::setPosition(float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}
  
float AbstractObject::getX()
{
  return this->x;
}

float AbstractObject::getY()
{
  return this->y;
}

float AbstractObject::getZ()
{
  return this->z;
}

ObjectSize AbstractObject::getSize()
{
    return this->size;
}

void AbstractObject::setSize(GLfloat width, GLfloat height, GLfloat depth)
{
    this->size.width = width;
    this->size.height = height;
    this->size.depth = depth;
}

GLuint AbstractObject::loadTexture(const char* imagePath)
{
   GLuint textureId;

   SDL_Surface* surface = IMG_Load(imagePath); 
   SDL_InvertSurface(surface);
   
   if (surface==NULL)
   {
      cout << "Impossibile caricare la texture " << imagePath << ": " << SDL_GetError() << endl;
      return 0;
   }

   glGenTextures(1,&textureId);
   
   glBindTexture(GL_TEXTURE_2D,textureId);

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w,surface->h, 0, GL_RGB,GL_UNSIGNED_BYTE, surface->pixels);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

   SDL_FreeSurface(surface);

   return textureId;
}



