#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <cstdlib>
#include <sstream>
using namespace std;

#include "Sky.h"
#include "Wall.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Camera.h"
#include "Player.h"
#include "Library.h"
#include "Scacchiera.h"
#include "GameEngine.h"
#include "FinishingLine.h"

#define MOVEMENT_SPEED 1/4
#define approx 0.3

class Game 
{
public:
  Game();
  ~Game();
  
  void gameMainLoop();
  bool collisionWithWall(float x, float y, float radius);
  bool collisionWithEnemy(float x, float y, int ind);
  bool collisionPlayerWithEnemy(float forwardX, float xPlayer, float forwardY, float yPlayer);
  
protected:  
  void BoomBoom();
  void drawWall();
  void createEnemyRandom();
  void createFinishingLine();
  
private:
  void processEvent();
  void processMovement();
  void processDown(SDL_Keysym& keysym);
  void processUp(SDL_Keysym& keysym);
  Sky* sky;
  Camera* camera;
  Player* player;
  GameEngine* gm;
  vector<Wall*> wall;
  Scacchiera* scacchi;
  vector<Enemy*> enemy;
  Bullet* bullet;
  FinishingLine* finishingLine;
  int life;
  GLfloat angolo;
  float start = 0;
  
  HudText* pauseText;
  HudText* winText;
  HudText* loseText;
  HudText* timerText;
  HudText* lifeText;
  
  bool quit;
  bool moveUp;
  bool moveDown;
  bool rotateLeft;
  bool rotateRight;
  bool boom;
  bool MOVE;
  bool win;
  bool lose;
  bool pause;
  bool collision = false;
  bool youLose = false;
};

#endif
