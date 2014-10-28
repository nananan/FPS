#ifndef HUDTEXT_H
#define HUDTEXT_H

#include <string>
using namespace std;

class HudText 
{
private:
  string text;
  int dim = 30;
  int x;
  int y;
  
public:
  HudText(int x, int y, string text);
  
  void setTextPosition(int x, int y);
  void setText(string text);
  void setDim(int dim);
  
  int getX();
  int getY();
  string getText();
  int getDim();
  
};

#endif
