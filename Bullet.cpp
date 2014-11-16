#include "Bullet.h"

Bullet::Bullet(Player* player, Camera* camera)
{
  this->player = player;
  this->camera = camera;
  angolo = player->getAngolo();
  float rad = angolo*3.14 / 180;
  setPosition(camera->getEyeX()+player->getSize().width+1.50, camera->getEyeY(), player->getSize().height/2);

  this->quad = gluNewQuadric();
  
  setSize(0.1, 0.1, 1.0);
  
}

void Bullet::render()
{
  glPushMatrix();
  
    glColor4f(0.0, 1.0, 1.0, 1.0);
    gluSphere(quad, 0.1, 10, 10);
  
  glPopMatrix();
}

void calcolaCoordinateEnemy(float& x, float& y, int in, int fin)
{
  x = rand()%fin + in;
  y = rand()%fin + in; 
}

bool collisionWithWall(float x, float y, float radius, vector<Wall*> wall)
{
  for (int i=0; i<wall.size(); i++)
  {
      if ( ((x + radius >= wall[i]->getX() && x + radius <= wall[i]->getX() + wall[i]->getSize().width) || 
	(x - radius >= wall[i]->getX() && x - radius <= wall[i]->getX() + wall[i]->getSize().width))	
	&& ((y + radius >= wall[i]->getY() && y + radius <= wall[i]->getY() + wall[i]->getSize().height) ||  
	(y - radius >= wall[i]->getY() && y - radius <= wall[i]->getY() + wall[i]->getSize().height)))
    {
      return true;
    }
  }
  return false;
}


bool Bullet::collision(Enemy* enemy, vector<Wall*> wall)
{
  srand(time(0));
  float rad = player->getAngolo()*3.14 / 180;
  float x1, y1;
  calcolaCoordinateEnemy(x1, y1, 10, 100);  
  
  if ((getX() >= enemy->getX()-enemy->getSize().width && getX() <= enemy->getX() + enemy->getSize().width)
  && (getY() >= enemy->getY()-enemy->getSize().height && getY() <= enemy->getY() + enemy->getSize().height))
  {
    while (collisionWithWall(x1, y1, enemy->getSize().width, wall))
      calcolaCoordinateEnemy(x1, y1, 10, 100);
    enemy->setPosition(x1, y1, 0.0);
    return true;
  }
  return false;
}

void Bullet::move()
{
  float rad = player->getAngolo()*3.14 / 180;
  
  float movement[2] = {getX(), getY()};
  
  movement[0] = movement[0] + cos(rad) * veloc;
  movement[1] = movement[1] + sin(rad) * veloc;
    
  setPosition(movement[0], movement[1], player->getSize().height/2);
}
