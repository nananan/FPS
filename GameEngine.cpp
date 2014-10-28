#include "GameEngine.h"

GameEngine:: GameEngine(int w, int h, const char* windowTitle)
{
  ambientLight[0] = 0.9;
  ambientLight[1] = 0.9;
  ambientLight[2] = 0.9;
  ambientLight[3] = 1.0;

  specular[0] = 0.9;
  specular[1] = 0.9;
  specular[2] = 0.9;
  specular[3] = 1.0;

  specref[0] = 0.2;
  specref[1] = 0.2;
  specref[2] = 0.2;
  specref[3] = 1.0;

  lightPos[0] = 0.7;
  lightPos[1] = 0.7;
  lightPos[2] = 0.9;
  lightPos[3] = 1.0;

  spotDir[0] = 0.0;
  spotDir[1] = 0.0;
  spotDir[2] = -1.0;

  initSDL(w, h, windowTitle);
  initGL(w, h);
}

GameEngine:: ~GameEngine()
{
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  
  Mix_FreeMusic(music);
  Mix_FreeMusic(win);
  Mix_FreeMusic(lose);
  Mix_CloseAudio();
  TTF_Quit();
  SDL_Quit();
}

bool GameEngine:: initSDL(int w, int h, const char* windowTitle)
{
  bool success = true;
  
  TTF_Init();
  
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    cout<<"ERRORE non può inizializzare SDL: "<< SDL_GetError()<<endl;
    success = false;
  }
  else
  {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    
    gWindow = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (gWindow == NULL)
    {
      cout<<"ERRORE impossibile inizializzare la finestra: "<< SDL_GetError()<<endl;
      success = false;
    }
    else
    {
      gContext = SDL_GL_CreateContext(gWindow);
      
      if (gContext == NULL)
      {
	cout<<"ERRORE non può inizializzare il Context: "<< SDL_GetError()<<endl;
	success = false;
      }
      else
      {
	if (SDL_GL_SetSwapInterval(1) < 0) 
	{
	  cout<<"non c'è il VSync, io vado avanti "<< SDL_GetError()<<endl;
	}
      }
    }
  }
  
  int flags=MIX_INIT_OGG|MIX_INIT_MOD;
  int initted=Mix_Init(flags);
  if(initted&flags != flags) 
  {
    printf("Mix_Init: Failed to init required ogg and mod support!\n");
    printf("Mix_Init: %s\n", Mix_GetError());
  }
  
  if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096 ) == -1 )
  {
    success = false;    
  }
  
  music = Mix_LoadMUS("audio/djShadow.ogg");
  win = Mix_LoadMUS("audio/win.ogg");
  lose = Mix_LoadMUS("audio/gameover.ogg");
  
  if (music == NULL || win == NULL || lose == NULL)
    cout<<"ERRORE: "<< Mix_GetError() <<endl;
  
  if (Mix_PlayMusic(music, -1) == -1)
  {
    success = false;
  }
    
  return success;
}

void GameEngine::renderText(int X, int Y, int dim, const string& Text)
{
  font = TTF_OpenFont( "fonts/DIGITALDREAMFATNARROW.ttf", dim);
  SDL_Surface *Message = TTF_RenderText_Blended(font, Text.c_str(), color);
  unsigned Texture = 0;
  
  if (X == -1)
  {
    X = (width/2) - Message->w/2;
  }
  if (Y == -1)
  {
    Y = (height/2) - Message->h/2;
  }
  
  SDL_InvertSurface(Message);

  glEnable(GL_TEXTURE_2D);
  
  glGenTextures(1, &Texture);
  glBindTexture(GL_TEXTURE_2D, Texture);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Message->w, Message->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, Message->pixels);

  glDepthMask(GL_FALSE);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  /*Draw this texture on a quad with the given xyz coordinates.*/
  glColor4f(1.0, 1.0, 1.0, 1.0);
  glBegin(GL_QUADS);
	  glTexCoord2d(0, 0); 
	  glVertex2f(X, Y);
	  glTexCoord2d(1, 0); 
	  glVertex2f(X+Message->w, Y);
	  glTexCoord2d(1, 1); 
	  glVertex2f(X+Message->w, Y+Message->h);
	  glTexCoord2d(0, 1); 
	  glVertex2f(X, Y+Message->h);
  glEnd();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  
  reshape(width, height);
  
  /*Clean up.*/
  glDeleteTextures(1, &Texture);
  glDisable(GL_TEXTURE_2D);
  SDL_FreeSurface(Message);
}

void GameEngine::setWin(bool WIN)
{
  this->WIN = WIN;
  Mix_PlayMusic(win, 0);
}

void GameEngine::setLose(bool LOSE)
{
  this->LOSE = LOSE;
  Mix_PlayMusic(lose, 0);
}

bool GameEngine::getFinish()
{
  return finishMusic;
}

void GameEngine::initGL(int w, int h)
{
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_LIGHTING);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,ambientLight);
  glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
  glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION,spotDir);
  glEnable(GL_LIGHT0);

  glEnable(GL_COLOR_MATERIAL);
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  glMaterialfv(GL_FRONT, GL_SPECULAR,specref);
  glMateriali(GL_FRONT, GL_SHININESS,1);

  glEnable(GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glClearColor (0.0, 0.0, 0.0, 1.0);
  
  reshape(w,h);
}

void GameEngine::reshape(int w, int h)
{
  width = w;
  height = h;
  glViewport (0, 0, w, h); 
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (float) w / (float) h, 1.0, 1024.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GameEngine::display()
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
  
  for (list<AbstractObject*>::iterator i=objectBeforeCamera.begin(); i!=objectBeforeCamera.end(); i++)
  {
    glPushMatrix();
      glTranslatef((*i)->getX(), (*i)->getY(), (*i)->getZ());
      (*i)->render();
    glPopMatrix();
  }
  
  gluLookAt(camera->getEyeX(), camera->getEyeY(), camera->getEyeZ(), camera->getForwardX(), camera->getForwardY(), camera->getForwardZ(), 0.0, 0.0, 1.0);
  
  for (list<AbstractObject*>::iterator i=objectAfterCamera.begin(); i!=objectAfterCamera.end(); i++)
  {
    glPushMatrix();
      glTranslatef((*i)->getX(), (*i)->getY(), (*i)->getZ());
      (*i)->render();
    glPopMatrix();
  }
  
  glPopMatrix();
  
  for (list<HudText*>::iterator i=text.begin(); i!=text.end(); i++)
  {
    renderText((*i)->getX(), (*i)->getY(), (*i)->getDim(), (*i)->getText());
  }
}

void GameEngine::addHudText(HudText* hudText)
{
  text.push_back(hudText);
}

void GameEngine::removeHudText(HudText* hudText)
{
  text.remove(hudText);
}

void GameEngine::update()
{
  display();

  SDL_GL_SwapWindow(gWindow);
}

void GameEngine::setCamera(Camera* camera)
{
  this->camera = camera;
}

void GameEngine::addObject(AbstractObject* object, bool before)
{
  if (before)
    objectBeforeCamera.push_back(object);
  else
    objectAfterCamera.push_back(object);
}

void GameEngine::removeObject(AbstractObject* object, bool before)
{
  if (before)
    objectBeforeCamera.remove(object);
  else
    objectAfterCamera.remove(object);
}
