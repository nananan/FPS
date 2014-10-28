#ifndef CAMERA_H
#define CAMERA_H

class Camera 
{
public:
  Camera(float eyeX, float eyeY, float eyeZ, float forwardX, float forwardY, float forwardZ);
  
  void setPosition(float eyeX, float eyeY, float eyeZ, float forwardX, float forwardY, float forwardZ);
  
  float getEyeX();
  float getEyeY();
  float getEyeZ();
  
  float getForwardX();
  float getForwardY();
  float getForwardZ();
  
private:
  float eyeX;
  float eyeY;
  float eyeZ;
  float forwardX;
  float forwardY;
  float forwardZ;
};

#endif
