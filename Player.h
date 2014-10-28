#ifndef PLAYER_H
#define PLAYER_H

#include "ModelLoader/model.h"

#include "Wall.h"
#include "Camera.h"
#include "Library.h"
#include "Scacchiera.h"
#include "AbstractObject.h"

#define appross 1.40

class Player: public AbstractObject
{
public:
  Player(Camera* camera, Scacchiera* scacchi, vector<Wall*> wall);
  virtual void render();
  
  void setLeft(bool move);
  void setRight(bool move);
  float getAngolo();
  void setAngolo(float angolo);
  
  bool collisionPlayerWithWall(float x, float y);
  
private:
  Camera* camera;
  Scacchiera* scacchi;
  Model* model;
  Model* model2;
  Model* model3;
  GLuint helmet;
  GLuint snail;
  GLuint snailhouse;
  vector<Wall*> wall;
  float rotateL = 0.0;
  float rotateR = 0.0;
  float angolo;
  
  bool moveLeft;
  bool moveRight;
  
};

#endif
