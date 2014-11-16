#include "FinishingLine.h"

FinishingLine::FinishingLine(GLfloat positionX, GLfloat positionY, GLfloat positionZ): AbstractObject()
{
  setPosition(positionX, positionY, positionZ);
  
  radius = 1.0;
  setSize(radius*2, radius*2, radius*2);
  
  this->quad = gluNewQuadric();
  gluQuadricTexture(this->quad, GLU_TRUE);
  this->textureId = loadTexture("texture/lol.png");
}

void FinishingLine::render()
{
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glEnable(GL_TEXTURE_2D);
  
  glPushMatrix();
    
    glRotatef(rotate, 0, 0, 1);
    if (!pause)
    {
      rotate += 1.0;
      if (rotate >= 360)
      rotate = 0;
    }
    
    glColor4f(1.0, 1.0, 1.0, 1.0);
    gluSphere(quad, radius, 20, 20);
    
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

GLfloat FinishingLine::getRadius()
{
  return radius;
}

void FinishingLine::setPause(bool pause)
{
  this->pause = pause;
}

bool FinishingLine::collisionLine(float forwardX, float xPlayer, float forwardY, float yPlayer)
{
  if ((forwardX + xPlayer + 0.1 >= getX() && forwardX + xPlayer + 0.1 <= getX() + getSize().width)
	&& (forwardY + yPlayer + 0.1 >= getY() && forwardY + yPlayer + 0.1 <= getY() + getSize().height))
    return true;
  return false;
}
