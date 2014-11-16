#include "HudText.h"
  
HudText::HudText(int x, int y, string text)
{
  this->text = text;
  dim = 30;
  color = {255, 255, 0, 255};
  this->x = x;
  this->y = y;
}
  
void HudText::setTextPosition(int x, int y)
{
  this->x = x;
  this->y = y;
}

void HudText::setText(string text)
{
  this->text = text;
}

void HudText::setDim(int dim)
{
  this->dim = dim;
}

void HudText::setColor(SDL_Color color)
{
  this->color = color;
}

SDL_Color HudText::getColor()
{
  return color;
}

int HudText::getX()
{
  return x;
}

int HudText::getY()
{
  return y;
}

string HudText::getText()
{
  return text;
}
 
int HudText::getDim()
{
  return dim;
}
