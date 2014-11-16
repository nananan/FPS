#include "Game.h"

Game::Game()
{
  gm = new GameEngine(1000, 1000, "Game");
  
  camera = new Camera(8.5, 52.33, 1.0, 9.5, 52.33, 1.0);
  sky = new Sky(100);
  scacchi = new Scacchiera();
  
  gm->setCamera(camera);
  gm->addObject(sky);
  gm->addObject(scacchi);
  
  drawWall();
  
  player = new Player(camera, scacchi, wall);
  
  gm->addObject(player, true);
  
  createEnemyRandom();
  createFinishingLine();
  
  life = 9;
  stringstream liv;
  liv<<"LIFE:"<<life;
  
  pauseText = new HudText(-1, -1, "pause");
  winText = new HudText(-1, -1, "winner XD");
  loseText = new HudText(-1, -1, "game over :(");
  timerText = new HudText(40, 650, "0");
  lifeText = new HudText(40, 600, liv.str());
  lifePlusText = new HudText(-1, -1, "+3");
  
  pauseText->setDim(60);
  winText->setDim(60);
  loseText->setDim(60);
  lifePlusText->setDim(100);
  
  pauseText->setColor(color);
  winText->setColor(color2);
  loseText->setColor(color2);
  lifePlusText->setColor(color2);
  
  gm->addHudText(timerText);
  gm->addHudText(lifeText);
  
  moveUp = false;
  moveDown = false;
  rotateLeft = false;
  rotateRight = false;
  boom = false;
  MOVE = false;
  lifePlus = false;
  lifePlusF = true;
  lifePlusSecond = false;
  
  cont = 0;
  
  angolo = 0.0;
  win = false;
  lose = false;
  pause = false;
  youLoseTime = false;
  
  start = SDL_GetTicks();
}

Game::~Game()
{
  delete gm;
  delete camera;
  delete scacchi;
  delete finishingLine;
  for (int i = 0; i < wall.size(); i++)
    delete wall[i];
  for (int i = 0; i < enemy.size(); i++)
    delete enemy[i];
}

void calcolaCoordinate(float& x, float& y, int in, int fin)
{
  x = rand()%fin + in;
  y = rand()%fin + in; 
}

void Game::gameMainLoop()
{
  quit = false;
  
  while (!quit)
  {    
    for (int i = 0; i < enemy.size(); i++)
    {
      if (!collisionWithEnemy(enemy[i]->getX(), enemy[i]->getY(), i))
	enemy[i]->move(camera);
    }
    
    if (MOVE)
    {
      bullet->move();
      if (collisionWithWall(bullet->getX(), bullet->getY(), 1.0))
      {
	gm->removeObject(bullet);
	MOVE = false;
      }
      for (int i = 0; i < enemy.size(); i++)
      {
	if (bullet->collision(enemy[i], wall))
	{
	  gm->removeObject(bullet);
	  MOVE = false;
	}  
      }
    }
    if (!pause)
    {
      start = SDL_GetTicks() - pausedTick;
      stringstream time;
      time <<"TIME:"<< (start / 1000);
      timerText->setText(time.str());
      if (start >= 150000)
	youLoseTime = true;
      if (cont == 0)
      {
	if (start >= 20000 && lifePlusF && life < 9)
	  lifePlus = true;
      }
      if (cont == 1)
      {
	if (start >= 23000)
	{
	  lifePlusF = true;
	  gm->removeHudText(lifePlusText);
	}
	if (start >= 50000 && lifePlusF && life < 9)
	  lifePlus = true;
      }
      if (cont == 2)
      {
	if (start >= 53000)
	{
	  lifePlusF = true;
	  gm->removeHudText(lifePlusText);
	}
	if (start >= 100000 && lifePlusF && life < 9)
	  lifePlus = true;
      }
      if (cont == 3)
      {
	if (start >= 103000)
	  gm->removeHudText(lifePlusText);
      }
    }
    else
    {
      pausedTick = start;
    }
    
    processEvent();
    if (!youLose && !collision)
    {
      processMovement();
      gm->update();
    }
    if (lifePlus)
    {
      plusLife();
      lifePlusF = false;
      lifePlus = false;
      cont++;
    }

    SDL_Delay(10);
  }
}

void Game::plusLife()
{
  if (life <= 7)
  {
    life += 2;
    lifePlusText->setText("+2");
  }
  else if (life == 8)
  {
    life += 1;
    lifePlusText->setText("+1");
  }
  stringstream lives;
  lives << "LIFE: "<< life;
  lifeText->setText(lives.str());
  gm->addHudText(lifePlusText);
}

void Game::drawWall()
{  
  wall.push_back(new Wall(0.0, 0.0, 0.0, 0, scacchi->getDim()));
  wall.push_back(new Wall(0.0, 0.0, 0.0, 1, scacchi->getDim()));
  wall.push_back(new Wall((scacchi->getDim()*5)-5, 0.0, 0.0, 1, scacchi->getDim()));  
  wall.push_back(new Wall(0.0, (scacchi->getDim()*5)-5, 0.0, 0, scacchi->getDim()));
  
  wall.push_back(new Wall(20.0, 0.0, 0.0, 1, 9));
  wall.push_back(new Wall(20.0, 40.0, 0.0, 0, 10));
  wall.push_back(new Wall(40.0, 0.0, 0.0, 1, 6));
  wall.push_back(new Wall(65.0, 10.0, 0.0, 1, 5));
  wall.push_back(new Wall(20.0, 60.0, 0.0, 1, 13));    //13 = (125 - 60) / 5
  wall.push_back(new Wall(20.0, 60.0, 0.0, 0, 10));
  wall.push_back(new Wall(40.0, 60.0, 0.0, 1, 9));
  wall.push_back(new Wall(60.0, 70, 0.0, 1, 11));
  wall.push_back(new Wall(80.0, (scacchi->getDim()*5)-50, 0.0, 1, 10));
  wall.push_back(new Wall(70.0, 100.0, 0.0, 0, 3));
  wall.push_back(new Wall(60.0, 80.0, 0.0, 0, 3));
  wall.push_back(new Wall(55.0, 20.0, 0.0, 0, 11));
  wall.push_back(new Wall(100.0, 0.0, 0.0, 1, 3));
  wall.push_back(new Wall(90.0, 20.0, 0.0, 1, 10));
  wall.push_back(new Wall(100.0, 40.0, 0.0, 0, 5));
  wall.push_back(new Wall(90.0, 80.0, 0.0, 0, 3));
  wall.push_back(new Wall(100.0, 75.0, 0.0, 0, 1));
  wall.push_back(new Wall(100.0, 75.0, 0.0, 0, 3));
  wall.push_back(new Wall(90.0, 60.0, 0.0, 0, 5));
  wall.push_back(new Wall(110.0, 90.0, 0.0, 1, 3));
  wall.push_back(new Wall(110.0, 90.0, 0.0, 0, 3));
  wall.push_back(new Wall(90.0, 90.0, 0.0, 1, 6));
  wall.push_back(new Wall(90.0, 100.0, 0.0, 0, 3));
  wall.push_back(new Wall(0.0, 20.0, 0.0, 0, 3));
  wall.push_back(new Wall(0.0, 80.0, 0.0, 0, 3));
  
  for (int i=0; i<wall.size(); i++)
    gm->addObject(wall[i]);
}

bool Game::collisionWithWall(float x, float y, float radius)
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

bool Game::collisionWithEnemy(float x, float y, int ind)
{
  for (int i = 0; i < enemy.size(); i++)
  {
    if (i != ind)
      if (x == enemy[i]->getX() + enemy[i]->getSize().width && y == enemy[i]->getY() + enemy[i]->getSize().height)
	return true;
  }
  return false;
}

void Game::createFinishingLine()
{
  srand(time(0));
  float x, y;

  while (collisionWithWall(x, y, 1.0) || collisionWithEnemy(x,y,-1))
      calcolaCoordinate(x, y, 30, 95);
  finishingLine = new FinishingLine(x, y, 1.0);
  
  gm->addObject(finishingLine);
}

void Game::createEnemyRandom()
{
  srand(time(0));
  float x, y;
  
  for (int i=0; i<20; i++)
  {
    calcolaCoordinate(x, y, 10, 100);
    
    while (collisionWithWall(x, y, 1.0))
	calcolaCoordinate(x, y, 10, 100);

    enemy.push_back(new Enemy(x, y, 0.0, wall, player));
  }
  for (int i=0; i<enemy.size(); i++)
  {
    gm->addObject(enemy[i]);
  }
}

bool Game::collisionPlayerWithEnemy(float eyeX, float xPlayer, float eyeY, float yPlayer)
{
  float x = 0, y = 0;
  
  for (int i = 0; i < enemy.size(); i++)
  {
    if (((eyeX + xPlayer>= enemy[i]->getX() && eyeX + xPlayer <= enemy[i]->getX() + enemy[i]->getSize().width)	||
      (eyeX + xPlayer >= enemy[i]->getX() && eyeX + xPlayer <= enemy[i]->getX() + enemy[i]->getSize().height) ||
      (eyeX - xPlayer >= enemy[i]->getX() && eyeX - xPlayer <= enemy[i]->getX() + enemy[i]->getSize().width) ||
      (eyeX - xPlayer >= enemy[i]->getX() && eyeX - xPlayer <= enemy[i]->getX() + enemy[i]->getSize().height))
    && ((eyeY + yPlayer >= enemy[i]->getY() && eyeY + yPlayer <= enemy[i]->getY() + enemy[i]->getSize().height) ||
	(eyeY + yPlayer >= enemy[i]->getY() && eyeY + yPlayer <= enemy[i]->getY() + enemy[i]->getSize().width) ||
	(eyeY - yPlayer >= enemy[i]->getY() && eyeY - yPlayer <= enemy[i]->getY() + enemy[i]->getSize().height) ||
	(eyeY - yPlayer >= enemy[i]->getY() && eyeY - yPlayer <= enemy[i]->getY() + enemy[i]->getSize().width)))
    {      
      while (collisionWithWall(x, y, enemy[i]->getSize().width))
	calcolaCoordinate(x, y, 10, 100);
      
      enemy[i]->setPosition(x, y, enemy[i]->getZ());
      
      return true;
    }
  }
  return false;
}

void Game::processEvent()
{
  SDL_Event e;

  while (SDL_PollEvent(&e) != 0)
  {
    if (e.type == SDL_QUIT)
      quit = true;
    else if (e.type == SDL_KEYDOWN)
      processDown(e.key.keysym);
    else if (e.type == SDL_KEYUP)
      processUp(e.key.keysym);
    else if (e.type == SDL_WINDOWEVENT)
    {
      if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
      {
	gm->reshape(e.window.data1, e.window.data2);
      }
    }
    else if (e.type == SDLK_p)
      processDown(e.key.keysym);
    else if (e.type == SDLK_SPACE)
      processDown(e.key.keysym);
  }
}

void Game::processMovement()
{
  float rad = angolo*3.14 / 180;
  float eye[3] = {camera->getEyeX(), camera->getEyeY(), camera->getEyeZ()};
  float forward[3] = {camera->getForwardX(), camera->getForwardY(), camera->getForwardZ()};

  if (!pause)
  {
    if (moveUp)
    {
      if (!player->collisionPlayerWithWall((camera->getEyeX() + cos(rad) * MOVEMENT_SPEED) + cos(rad) * (player->getSize().width+1.50), (camera->getEyeY() + sin(rad) * MOVEMENT_SPEED) + sin(rad) * (player->getSize().width+1.50)) && !player->collisionPlayerWithWall((camera->getEyeX() + cos(rad) * MOVEMENT_SPEED) + cos(rad) * (player->getSize().width+(player->getSize().height/2)+1.50), (camera->getEyeY() + sin(rad) * MOVEMENT_SPEED) + sin(rad) * (player->getSize().width+(player->getSize().height/2)+1.50)))
      {
	eye[0] = camera->getEyeX() + cos(rad) * MOVEMENT_SPEED;
	eye[1] = camera->getEyeY() + sin(rad) * MOVEMENT_SPEED;
	forward[0] = camera->getForwardX() + cos(rad) * MOVEMENT_SPEED;
	forward[1] = camera->getForwardY() + sin(rad) * MOVEMENT_SPEED;
      }
    }
    else if (moveDown)
    {
      if (!player->collisionPlayerWithWall((camera->getEyeX() - cos(rad) * MOVEMENT_SPEED) - cos(rad) * (player->getSize().width+1.50), (camera->getEyeY() - sin(rad) * MOVEMENT_SPEED) - sin(rad) * (player->getSize().width+1.50)))
      {
	eye[0] = camera->getEyeX() - cos(rad) * MOVEMENT_SPEED;
	eye[1] = camera->getEyeY() - sin(rad) * MOVEMENT_SPEED;
	forward[0] = camera->getForwardX() - cos(rad) * MOVEMENT_SPEED;
	forward[1] = camera->getForwardY() - sin(rad) * MOVEMENT_SPEED;
      }
    }
    if (rotateLeft)
    {
      angolo += 2;
      rad = angolo*3.14 / 180;
      if (!player->collisionPlayerWithWall((camera->getEyeX() + cos(rad) * MOVEMENT_SPEED) + cos(rad) * (player->getSize().width+1.50), (camera->getEyeY() + sin(rad) * MOVEMENT_SPEED) + sin(rad) * (player->getSize().width+1.50)))
      {
	forward[0] = eye[0] + cos(rad);
	forward[1] = eye[1] + sin(rad);
      
	player->setLeft(true);
      }
      else
      {
	angolo -= 2;
	rad = angolo*3.14 / 180;
      }
    }
    if (rotateRight)
    {
      angolo -= 2;
      rad = angolo*3.14 / 180;
      if (!player->collisionPlayerWithWall((camera->getEyeX() + cos(rad) * MOVEMENT_SPEED) + cos(rad) * (player->getSize().width+1.50), (camera->getEyeY() + sin(rad) * MOVEMENT_SPEED) + sin(rad) * (player->getSize().width+1.50)))
      {
	forward[0] = eye[0] + cos(rad);
	forward[1] = eye[1] + sin(rad);
      
	player->setRight(true);
      }
      else
      {
	angolo += 2;
	rad = angolo*3.14 / 180;
      }
    }
    
    player->setAngolo(angolo);
    camera->setPosition(eye[0], eye[1], camera->getEyeZ(), forward[0], forward[1], camera->getForwardZ());
  }
  
  if (finishingLine->collisionLine(camera->getForwardX(), player->getSize().width, camera->getForwardY(), player->getSize().height))
  {
    deleteObject();
    gm->setWin(win);
    collision = true;
    gm->addHudText(winText);
  }

  if (collisionPlayerWithEnemy(camera->getEyeX(), player->getSize().width, camera->getEyeY(), player->getSize().height))
  {
      life --;
      stringstream lives;
      lives << "LIFE: "<< life;
      lifeText->setText(lives.str());
  }
          
  if (life == 0 || youLoseTime)
  {
    deleteObject();
    youLose = true;
    gm->setLose(youLose);
    if (youLoseTime)
    {
      stringstream time;
      time << "TIME: ";
      timerText->setText(time.str() + "is Over");
    }
    gm->addHudText(loseText);
  }
}

void Game::BoomBoom()
{
  if (!pause)
  {
    gm->removeObject(bullet);
    bullet = new Bullet(player, camera);
    bullet->setPosition(camera->getEyeX(), camera->getEyeY(), player->getSize().height/2);
    gm->addObject(bullet);
  }
}

void Game::processDown(SDL_Keysym& keysym)
{
  if (keysym.sym == SDLK_ESCAPE)
    quit = true;
  else if (keysym.sym == SDLK_UP)
    moveUp = true;
  else if (keysym.sym == SDLK_DOWN)
    moveDown = true;
  else if (keysym.sym == SDLK_LEFT)
    rotateLeft = true;
  else if (keysym.sym == SDLK_RIGHT)
    rotateRight = true;
  else if (keysym.sym == SDLK_p)
  {
    if (Mix_PausedMusic() == 0)
    {
      pause = true;
      gm->addHudText(pauseText);
      for (int i = 0; i < enemy.size(); i++)
	enemy[i]->setPause(true);
      Mix_PauseMusic();
      
      finishingLine->setPause(true);
      
      pausedTick = SDL_GetTicks() - start;
    }
    else
    {
      pause = false;
      gm->removeHudText(pauseText);
      for (int i = 0; i < enemy.size(); i++)
	enemy[i]->setPause(false);
      Mix_ResumeMusic();
      
      finishingLine->setPause(false);
      
      pausedTick = SDL_GetTicks() - start;
    }
  }
  else if (keysym.sym == SDLK_SPACE)
  {
    BoomBoom();
    boom = true;
    MOVE = true;
  }
}

void Game::processUp(SDL_Keysym& keysym)
{
  if (keysym.sym == SDLK_UP)
    moveUp = false;
  else if (keysym.sym == SDLK_DOWN)
    moveDown = false;
  else if (keysym.sym == SDLK_LEFT)
    rotateLeft = false;
  else if (keysym.sym == SDLK_RIGHT)
    rotateRight = false;
  else if (keysym.sym == SDLK_SPACE)
  {
    boom = false;
  }
}

void Game::deleteObject()
{
  gm->removeObject(player, true);
  for (int i=0; i<wall.size(); i++)
    gm->removeObject(wall[i]);
  for (int i=0; i<enemy.size(); i++)
    gm->removeObject(enemy[i]);
  gm->removeObject(sky);
  gm->removeObject(scacchi);
  gm->removeObject(finishingLine);
}
