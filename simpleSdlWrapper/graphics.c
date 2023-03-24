#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define GRAPHICS

#if defined(_WIN32)
#include "SDL_ttf.h"
#endif

#if defined(linux)
#include "SDL2/SDL_ttf.h"
#endif

#include "imagen.h"
#include "graphics.h"

SDL_Window* window = { NULL };

int colorR, colorG, colorB;

SDL_Renderer* gRenderer;
SDL_Renderer* getRenderer() { return gRenderer; }

int sgHasieratu(int width, int height, Uint32 flags)
{
  //SDL_Surface* iconoa = SDL_LoadBMP(APLIKAZIO_IKONOA);
  int ret = 0;

  if (SDL_WasInit(SDL_INIT_EVERYTHING) == 0) {
	  if (SDL_Init(SDL_INIT_VIDEO) < 0)
	  {
		  fprintf(stderr, "ezin SDL hasieratu: %s\n", SDL_GetError());
		  return -1;
	  }

	  atexit(SDL_Quit);
  }
  window = SDL_CreateWindow("Main Menu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);//AITOR_EDIT
 // SDL_SetWindowIcon(window[sg], iconoa);
  if (window == NULL)
  {
    fprintf(stderr, "Ezin lehioa sortu: %s\n", SDL_GetError());
    return -1;
  }
  gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  TTF_Init();
  atexit(TTF_Quit);
  return ret;
}

void sgItxi()
{
  SDL_DestroyWindow(window);
  //SDL_Quit();//AITOR_EDIT
}

void arkatzKoloreaEzarri(int red, int green, int blue)
{
  colorR = red;
  colorG = green;
  colorB = blue;
}

void zuzenaMarraztu(int x1, int y1, int x2, int y2)
{
  SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}

void puntuaMarraztu(int x, int y)
{
  SDL_SetRenderDrawColor(gRenderer, colorR, colorG, colorB, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoint(gRenderer, x, y);
}

int irudiaMarraztu(SDL_Texture* texture, SDL_Rect *pDest)
{
  SDL_Rect src;

  src.x = 0;
  src.y = 0;
  src.w = pDest->w;
  src.h = pDest->h;
  SDL_RenderCopy(gRenderer, texture, &src, pDest);
  return 0;
}

void pantailaGarbitu()
{
  SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(gRenderer);
}

void pantailaBerriztu()
{
  SDL_RenderPresent(gRenderer);
}
