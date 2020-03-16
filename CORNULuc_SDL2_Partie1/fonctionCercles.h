#ifndef FONCTIONCERCLES_H_INCLUDED
#define FONCTIONCERCLES_H_INCLUDED
#include <stdio.h>
#include "SDL.h"
#include <math.h>

int cercleVide(SDL_Renderer *pRenderer, int xCircle, int yCircle, int radiusCircle, int nbPoints);
int cerclePlein(SDL_Renderer *pRenderer, int xCircle, int yCircle, int radiusCircle, int nbPoints);

#endif
