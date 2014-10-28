#include <iostream>
using namespace std;

#include "Game.h"

int main(int argc, char** argv)
{
  Game* game = new Game();
  
  game->gameMainLoop();
  
  delete game;
  
  return 0;
}
