#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "Camera.h"
#include "HudText.h"
#include "AbstractObject.h"

#include <list>
#include <iostream>
using namespace std;

class GameEngine 
{
public:
  GameEngine(int w, int h, const char* windowTitle);
  ~GameEngine();
  
  void update();
  void setCamera(Camera* camera);
  void addObject(AbstractObject* object, bool before = false);
  void removeObject(AbstractObject* object, bool before = false);
  void addHudText(HudText* hudText);
  void removeHudText(HudText* hudText);
  
  void setWin(bool WIN);
  void setLose(bool LOSE);
  bool getFinish();
  
  void display();
  void reshape(int w, int h);

private:
  void initGL(int w, int h);
  bool initSDL(int w, int h, const char* windowTitle);
  void renderText(int X, int Y, int dim, const string& Text);
  list<AbstractObject*> objectAfterCamera;
  list<AbstractObject*> objectBeforeCamera;
  list<HudText*> text;
  Camera* camera;
  SDL_Window* gWindow;
  SDL_GLContext gContext;
  GLfloat ambientLight[4];
  GLfloat specular[4];
  GLfloat specref[4];
  GLfloat lightPos[4];
  GLfloat  spotDir[3];
  SDL_Color color = { 255, 255, 0, 255 };
  
  bool WIN = false;
  bool LOSE = false;
  bool finishMusic = false;
  
  Mix_Music *music;
  Mix_Music *win;
  Mix_Music *lose;
  
  TTF_Font *font;
  
  int width;
  int height;
};

#endif
