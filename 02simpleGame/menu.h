#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "graphics.h"
#include "ebentoak.h"
#include "text.h"
#include "mapa.h"

#define MAX_MAPA 10
#define SAGU_GURPILA_ABIADURA 10
#define MENU_MAPAK_MARGEN 50
#define MENU_MAPAK_LAUKIAK { MENU_MAPAK_MARGEN, MENU_MAPAK_MARGEN, 300, 200 }

typedef enum egoera { ITXI, MENU, MAPAK, SIMULAZIOA} EGOERA;

//1. PANTAILA - MENU
int menuMain();

//Menuaren botoiak (laukiak) pantailaratu
void menuMainBotoiak(SDL_Rect botoiak[]);

//Menuaren botoien textuak pantailaratu
void menuMainTextuak();

//Menuaren botoietan klik egin den edo ez (eta zein klikatu den)
int menuMainBotoienBarruanAlDa(SDL_Rect botoiak[], int botoiKop, POSIZIOA pos);

//2. PANTAILA - MAPAK
int menuMapak(int *mapaAukera);

//Mapak aukeratzeko botoiak pantailaratu
void menuMapakLaukiak(SDL_Rect lauki, int laukiKop, MAPA **mapa);

//Mapak aukeratzeko botoietan klik egin den edo ez (eta zein klikatu den)
int menuMapakBotoiak(POSIZIOA saguPos, SDL_Rect lauki, int laukiKop);

//Mapa aukeratzean agertzen den textua
void menuSimulazioInstruzioak(MAPA *mapa);

//Simulazioan: "ESC menu-ra bueltatzeko"
void menuSimulazioMenuBueltatu(MAPA mapa);

//Simulazioan: "'r' hasierako posiziora bueltatzeko"
void menuSimulazioBideErrepikatu(MAPA mapa);

#endif
