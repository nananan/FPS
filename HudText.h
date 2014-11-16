#ifndef HUDTEXT_H
#define HUDTEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include <string>
using namespace std;

class HudText 
{
private:
  string text;
  int dim;
  SDL_Color color;
  int x;
  int y;
  
public:
  HudText(int x, int y, string text);
  
  void setTextPosition(int x, int y);
  void setText(string text);
  void setDim(int dim);
  void setColor(SDL_Color color);
  
  int getX();
  int getY();
  string getText();
  int getDim();
  SDL_Color getColor();
  
};

#endif
