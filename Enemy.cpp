#include "Enemy.h"

Enemy::Enemy(GLfloat positionX, GLfloat positionY, GLfloat positionZ, vector<Wall*> wall, Player* player): AbstractObject()
{
  setPosition(positionX, positionY, positionZ);
  
  radius = 1.0;
  
  this->model = new Model();
  model->loadModel("CreeperOne/CreeperOne.obj");
  model->scaleModel(0.8);
  model->calcDim();
  
  creeper = model->getGlList();
  
  this->wall = wall;
  this->player = player;
  setSize(model->getDim().width, model->getDim().height, model->getDim().depth);
}

void Enemy::render()
{
  glPushMatrix();
    glRotatef(90, 1, 0, 0);
    
    if (rotateL)
    {
      glRotatef(360, 0, 1, 0);
      rotateL = false;
    }
    else if (rotateR)
    {
      glRotatef(180, 0, 1, 0);
      rotateR = false;
    }
    else if (rotateA)
    {
      glRotatef(angolo, 0, 1, 0);
      rotateA = false;
    }
    else if (rotateAll)
    {
      glRotatef(angolo+90, 0, 1, 0);
      rotateAll = false;
    }
    else if (rotateAllB)
    {
      glRotatef(angolo-90, 0, 1, 0);
      rotateAllB = false;
    }
//     model->drawModel();
    glCallList(creeper);
  
  glPopMatrix();
}

GLfloat Enemy::getRadius()
{
  return radius;
}

bool Enemy::collisionWall(float rad)
{
  for (int i = 0; i < wall.size(); i++)
  {
    if ( (((getX()+sin(rad)*velocity)+sin(rad)*(getSize().width + getSize().depth)) >= wall[i]->getX() && ((getX()+sin(rad)*velocity)+sin(rad)*(getSize().width + getSize().depth)) <= wall[i]->getX() + wall[i]->getSize().width)
    && (((getY()+cos(rad)*velocity)+cos(rad)*(getSize().width + getSize().depth)) >= wall[i]->getY() && ((getY()+cos(rad)*velocity)+cos(rad)*(getSize().width + getSize().depth)) <= wall[i]->getY() + wall[i]->getSize().height))
    {
      return true;
    }
  }
  return false;
}

// void Enemy::move(Camera* camera)
// {
//   float rad = angolo*3.14 / 180;
//   int lungVista = 200;
//   float X = getX() + lungVista * cos(rad);
//   float Y = getY() + lungVista * sin(rad);
//   
//   float moveEnemy[2] = {getX(), getY()};
// 
//   if (!visto)
//   {
//     angolo += 1;
//     rotateAll = true;
//     X = getX() + lungVista * cos(rad);
//     Y = getY() + lungVista * sin(rad);
//   }
//   
//   if (angolo >= 360)
//     angolo = 0;
//   rad = angolo*3.14 / 180;
//   
//   if (iCanSee(X, Y, (camera->getEyeX()+3 ), (camera->getEyeY()-2.1)))
//   {
//     moveEnemy[0] = moveEnemy[0] + cos(rad) * velocity;
//     moveEnemy[1] = moveEnemy[1] + sin(rad) * velocity;
//     setPosition(moveEnemy[0], moveEnemy[1], getZ());
//     visto = true;
//   }
//   else
//     visto = false;
//   
// }
// 
// bool Enemy::iCanSee(float X, float Y, float pX, float pY)
// {
//   float calcolo = ((pY - getY()) / (Y -getY())) - ((pX - getX()) / (X -getX()));
//   if (calcolo < 0)
//     calcolo *= -1;
//   
//   if ((calcolo >= 0 && calcolo <= 0.05) && 
//      (((pX >= getX() && pX <= X) && (pY >= getY() && pY <= Y)) || ((pX <= getX() && pX >= X) && (pY <= getY() && pY >= Y))))
//   {
//     cout<<"TI VEDO"<<endl;
//     return true;
//   }
//   return false;
// }


void Enemy::move(Camera* camera)
{
  float rad = angolo*3.14 / 180;
  float moveEnemy[2] = {getX(), getY()};
  
  if (!pause)
  {
    if (!collisionWall(rad))
    {
      if (camera->getForwardX() > getX() && (camera->getForwardY() <= getY()+velocity && camera->getForwardY() >= getY()-velocity))
      {
	num_move = 1;
	float angoloOld = angolo;
	angolo = 90;
	rad = angolo*3.14 / 180;
	if (!collisionWall(rad))
	{
	  rotateA = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = camera->getForwardY();
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardX() < getX() && (camera->getForwardY() <= getY()+velocity && camera->getForwardY() >= getY()-velocity))
      {
	num_move = 2;
	float angoloOld = angolo;
	angolo = -90;
	rad = angolo*3.14 / 180;
	if (!collisionWall(rad))
	{
	  rotateA = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = camera->getForwardY();
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardY() > getY() && (camera->getForwardX() <= getX()+velocity && camera->getForwardX() >= getX()-velocity))
      {
	num_move = 3;
	float angoloOld = angolo;
	angolo = 0;
	rad = angolo*3.14 / 180;
	if (!collisionWall(rad))
	{
	  rotateR = true;
	  moveEnemy[0] = camera->getForwardX();
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardY() < getY() && (camera->getForwardX() <= getX()+velocity && camera->getForwardX() >= getX()-velocity))
      {
	num_move = 4;
	float angoloOld = angolo;
	angolo = 180;
	rad = angolo*3.14 / 180;
	if (!collisionWall(rad))
	{
	  rotateL = true;
	  moveEnemy[0] = camera->getForwardX();
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardX() > getX() && camera->getForwardY() > getY())
      {
	num_move = 5;
	float angoloOld = angolo;
	angolo = 45;
	rad = angolo*3.14 / 180;
	if (!collisionWall(rad))
	{
	  rotateAll = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardX() < getX() && camera->getForwardY() < getY())
      {
	num_move = 6;
	float angoloOld = angolo;
	angolo = -135;
	rad = angolo*3.14 / 180;

	if (!collisionWall(rad))
	{
	  rotateAll = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardX() < getX() && camera->getForwardY() > getY())
      {
	num_move = 7;
	float angoloOld = angolo;
	angolo = -45;
	rad = angolo*3.14 / 180;

	if (!collisionWall(rad))
	{
	  rotateAllB = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
      else if (camera->getForwardX() > getX() && camera->getForwardY() < getY())
      {
	num_move = 8;
	float angoloOld = angolo;
	angolo = 135;
	rad = angolo*3.14 / 180;
	
	if (!collisionWall(rad))
	{
	  rotateAllB = true;
	  moveEnemy[0] = moveEnemy[0] + sin(rad) * velocity;
	  moveEnemy[1] = moveEnemy[1] + cos(rad) * velocity;
	}
	else
	{
	  angolo = angoloOld;
	  rad = angolo*3.14 / 180;
	}
      }
    }
    else
    {
      float angoloOld = angolo;
      angolo += 180;
      if (angolo >= 360)
	angolo = fmod(angolo, 360);
      rad = angolo*3.14 / 180;
      rotateAll = true;
    }
    
    setPosition(moveEnemy[0], moveEnemy[1], getZ());
  }
  else
  {
    if (num_move == 1)
      rotateA = true;
    else if (num_move == 2)
      rotateA = true;
    else if (num_move == 3)
      rotateR = true;
    else if (num_move == 4)
      rotateL = true;
    else if (num_move == 5)
      rotateAll = true;
    else if (num_move == 6)
      rotateAll = true;
    else if (num_move == 7)
      rotateAllB = true;
    else if (num_move == 8)
      rotateAllB = true;
  }
}

void Enemy::setPause(bool pause)
{
  this->pause = pause;
}
