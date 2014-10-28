#include "Camera.h"

Camera::Camera(float eyeX, float eyeY, float eyeZ, float forwardX, float forwardY, float forwardZ)
{
  setPosition(eyeX, eyeY, eyeZ, forwardX, forwardY, forwardZ);
}

void Camera::setPosition(float eyeX, float eyeY, float eyeZ, float forwardX, float forwardY, float forwardZ)
{
  this->eyeX = eyeX;
  this->eyeY = eyeY;
  this->eyeZ = eyeZ;
  
  this->forwardX = forwardX;
  this->forwardY = forwardY;
  this->forwardZ = forwardZ;
}

float Camera::getEyeX()
{
  return this->eyeX;
}

float Camera::getEyeY()
{
  return this->eyeY;
}

float Camera::getEyeZ()
{
  return this->eyeZ;
}

float Camera::getForwardX()
{
  return this->forwardX;
}

float Camera::getForwardY()
{
  return this->forwardY;
}

float Camera::getForwardZ()
{
  return this->forwardZ;
}
