#ifndef GRAPHICS_H
#define GRAPHICS_H
#if defined(_WIN32)
#include "SDL.h"
#endif

#if defined(linux)
#include <SDL2/SDL.h>
#endif

#define SCREEN_WIDTH 1200//750//640
#define SCREEN_HEIGHT 700//600//480

int sgHasieratu(int width, int height, Uint32 flags);
void sgItxi();
void arkatzKoloreaEzarri(int red, int green, int blue);
void puntuaMarraztu(int x, int y);
void zuzenaMarraztu(int x1, int y1, int x2, int y2);

void pantailaGarbitu();
void pantailaBerriztu();

int irudiaMarraztu(SDL_Texture* texture, SDL_Rect *pDest);

SDL_Renderer* getRenderer();

#endif
