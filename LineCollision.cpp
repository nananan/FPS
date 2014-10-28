#include "LineCollision.h"
   
LineCollision::LineCollision(Player* player, Camera* camera): AbstractObject()
{
  this->player = player;
  setPosition(player->getX(), player->getY(), player->getZ());
  
//   setSize(player->getSize().width+3.0, player->getSize().height, 1.0);
  
}

void LineCollision::render()
{
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
//     glRotatef(-90, 0, 1, 0);
   glBegin(GL_LINES);
      //glVertex3f (0.25, 0.25, 0.0);
      //glVertex3f (0.75, 0.25, 0.0);
      glVertex3f (0.25, 0.25, 0.0);
      glVertex3f (0.75, 0.25, 0.0);
   glEnd();
  glPopMatrix();
}
