#include "Sky.h"

Sky::Sky(GLfloat size)
{
    setPosition(0, 0, 0);
    setSize (size, size, size);

    this->quad = gluNewQuadric();
    gluQuadricTexture(this->quad, GLU_TRUE);

    this->textureId = loadTexture("texture/sky.png");
}

void Sky::render()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslated(getX(),getY(),getZ());
    glColor4f(1.0, 1.0, 1.0, 1.0);
    gluSphere(quad, getSize().width*3, 10, 10);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
