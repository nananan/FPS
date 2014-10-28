#ifndef SDLFIX_H
#define SDLFIX_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

  int invert_image(int pitch, int height, void* image_pixels);
  int SDL_InvertSurface(SDL_Surface* image);

#endif
