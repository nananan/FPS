#include "Scacchiera.h"
#include <iostream>
using namespace std;

Scacchiera::Scacchiera(): AbstractObject()
{
  dim = 25;
  setSize (dim, dim, dim);
  
  this->textureId = loadTexture("texture/clover.png");
}

void Scacchiera::render()
{
  glBindTexture(GL_TEXTURE_2D, textureId);

  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslated(getX(),getY(),getZ());
  glColor4f(1.0, 1.0, 1.0, 1.0);
  
  for (int i= 0; i < dim; i++)
  {
    for (int k = 0; k < dim; k++)
    {
      glBegin(GL_QUADS);               
	glTexCoord2d(5*i, 5*k);
	glVertex2d( 5*i, 5*k);
	
	glTexCoord2d(5*i+5, 5*k);
	glVertex2d( 5*i+5, 5*k);
	
	glTexCoord2d(5*i+5, 5*k+5);
	glVertex2d( 5*i+5, 5*k+5);
	
	glTexCoord2d(5*i, 5*k+5);
	glVertex2d( 5*i, 5*k+5);
      glEnd();
    }
  }   

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

float Scacchiera::getDim()
{
  return dim;
}
