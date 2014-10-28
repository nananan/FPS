#include "HudText.h"
  
HudText::HudText(int x, int y, string text)
{
  this->text = text;
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
