#include "Player.h"

Player::Player(Camera* camera, Scacchiera* scacchi, vector<Wall*> wall): AbstractObject()
{
  this->camera = camera;
  this->scacchi = scacchi;
  this->wall = wall;
  
  setPosition(0, 0, 0);
  
  this->model = new Model();
  this->model2 = new Model();
  this->model3 = new Model();
  model->loadModel("snail/snail.obj");
  model2->loadModel("snail/helmet.obj");
  model3->loadModel("snail/snailhouse.obj");
  
  model->scaleModel(0.09);
  model2->scaleModel(0.09);
  model3->scaleModel(0.07);
  model->calcDim();
  
  snail = model->getGlList();
  helmet = model2->getGlList();
  snailhouse = model3->getGlList();
  
  setSize(model->getDim().width, model->getDim().height, model->getDim().depth);
//   model->getModelInfo();
}

void Player::render()
{
  glPushMatrix();
     glTranslated(0.0, -0.9, -model->getDim().width-1);
     glRotatef(-90, 0, 1, 0);
     
     if (moveLeft)
     {
       glRotatef(45, 1, 1, 0);
       moveLeft = false;
     }
     else if (moveRight)
     {
       glRotatef(-45, 1, 1, 0);
       moveRight = false;
     }
     
     glCallList(snail);
     glCallList(helmet);
     glCallList(snailhouse);
     
  glPopMatrix();
}

void Player::setLeft(bool move)
{
  moveLeft = move;
}

void Player::setRight(bool move)
{
  moveRight = move;
}

bool Player::collisionPlayerWithWall(float x, float y)
{
  for (int i = 0; i < wall.size(); i++)
  {
    if ((x+appross <= wall[i]->getX() + wall[i]->getSize().width && x+appross >= wall[i]->getX())
      && (y+appross <= wall[i]->getY() + wall[i]->getSize().height && y+appross >= wall[i]->getY()) || 
    (x-appross <= wall[i]->getX() + wall[i]->getSize().width && x-appross >= wall[i]->getX())
      && (y-appross <= wall[i]->getY() + wall[i]->getSize().height && y-appross >= wall[i]->getY()))
      return true;
  }
  return false;
}

float Player::getAngolo()
{
  return angolo;
}

void Player::setAngolo(float angolo)
{
  this->angolo = angolo;
}
