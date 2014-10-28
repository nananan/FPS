#include "Wall.h"

Wall:: Wall(float x, float y, float z, int dir, int dim): AbstractObject()
{
  setPosition(x, y, z);
  
  if (dir == 1)
    setSize(5.0, 5*dim, heig);
  else 
    setSize(5*dim, 5.0, heig);

  this->dir = dir;
  this->dim = dim;
  
  this->textureId = loadTexture("texture/muro.png");
}

int Wall::getDim()
{
  return dim;
}

int Wall::getDir()
{
  return dir;
}

void Wall::render()
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textureId);
  
  glPushMatrix();
   
  glColor4f(1.0, 1.0, 1.0, 1.0);
  
  for (int i=0; i<dim; i++)
  {
    if (dir == 0)
    {
      if (i > 0)
	glTranslated(5.0, 0.0, 0.0);
      
      glBegin(GL_QUADS);
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 0.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 0.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 0.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 0.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 5.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 5.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 5.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 5.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 0.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 5.0, 0.0);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 0.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(0.0, 5.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(0.0, 5.0, 0.0);
	
	glTexCoord2d (0, 0);
	glVertex3d(5.0, 0.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(5.0, 0.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 5.0, 0.0);
      glEnd();
    }
    if (dir == 1)
    {
      if (i > 0)
	glTranslated(0.0, 5.0, 0.0);
      
      glBegin(GL_QUADS);
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(0.0, 5.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(0.0, 5.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 0.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(0.0, 5.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(5.0, 0.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(5.0, 0.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 5.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (0, 1);
	glVertex3d(5.0, 0.0, heig);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (1, 0);
	glVertex3d(0.0, 5.0, 0.0);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(5.0, 0.0, 0.0);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 0.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 0.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 0.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 0.0, 0.0);
	
	glTexCoord2d (0, 0);
	glVertex3d(0.0, 5.0, 0.0);
	glTexCoord2d (0, 1);
	glVertex3d(0.0, 5.0, heig);
	glTexCoord2d (1, 1);
	glVertex3d(5.0, 5.0, heig);
	glTexCoord2d (1, 0);
	glVertex3d(5.0, 5.0, 0.0);
      glEnd();
    }
  }
    
  glPopMatrix();
  
  glDisable(GL_TEXTURE_2D);
}
