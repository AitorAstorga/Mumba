#if defined(_WIN32)
#include "SDL.h"
#include "SDL_ttf.h"
#endif

#if defined(linux)
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "text.h"
#include "graphics.h"
#include "imagen.h"
#include <stdio.h>

TTF_Font *font=0;
#if defined(_WIN32)
#define FONT "C:\\WINDOWS\\Fonts\\ARIAL.TTF"
#endif

#if defined(linux)
#define FONT "/usr/share/fonts/truetype/DejaVuSans.ttf"
#endif

void textuaGaitu(int textuTamaina){
	font=TTF_OpenFontIndex(FONT, textuTamaina, 0);
	if(!font) 
  {
		printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
		// handle error
	}
}

void textuaIdatzi(int x, int y, char *str, int sg, SDL_Color textColor)
{
  SDL_Surface* textSurface;
  SDL_Texture *mTexture;
  //SDL_Color textColor = { 0XFF, 0XFF, 0XFF };
  SDL_Rect src, dst;

  if (font == 0) return;
  textSurface = TTF_RenderText_Solid(font, str, textColor);
  mTexture = SDL_CreateTextureFromSurface(getRenderer(), textSurface);
  src.x = 0; dst.x = x;
  src.y = 0; dst.y = y;
  src.w = dst.w = textSurface->w;
  src.h = dst.h = textSurface->h;
  SDL_RenderCopy(getRenderer(), mTexture, &src, &dst);
  SDL_FreeSurface(textSurface);
  SDL_DestroyTexture(mTexture);
}

void textuaDesgaitu(void)
{
  if (font != 0) TTF_CloseFont(font);
  font = 0;
}
