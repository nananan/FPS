#ifndef ENEMY_H
#define ENEMY_H

#include "ModelLoader/model.h"

#include "Wall.h"
#include "Camera.h"
#include "Player.h"
#include "Library.h"
#include "AbstractObject.h"

#define velocity 0.09

class Enemy: public AbstractObject
{
public:
  Enemy(GLfloat positionX, GLfloat positionY, GLfloat positionZ, vector<Wall*> wall, Player* player);
  GLfloat getRadius();
  virtual void render();
  void move(Camera* camera);
  bool collisionWall(float rad);
  void setPause(bool pause);
  
private:
  GLfloat radius;
  GLUquadric* quad;
  GLuint textureId;
  Model* model;
  GLuint creeper;
  vector<Wall*> wall;
  Player* player;
  float angolo = 0;
  int num_move = 0;
  
  bool rotateL;
  bool rotateR;
  bool rotateAll;
  bool rotateAllB;
  bool rotateA;
  bool visto = false;
  bool pause = false;
  
  bool iCanSee(float X, float Y, float pX, float pY);
};

#endif
