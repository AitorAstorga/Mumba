#include <stdio.h>

#include "mapa.h"
#include "menu.h"
#include "gehigarriak.h"
#include "dijkstra.h"
#include <math.h>

#include <string.h>

#if defined(_WIN32)
#include "SDL.h"
#endif

#if defined(linux)
#include <SDL2/SDL.h>
#endif

void simulazioMugimenduakExekutatu(MAPA mapa, NODO_ERPINA* bidea);

int simulazioa(MAPA* mapa);

int main(int argc, char* argv[]) {
	MAPA *mapa = NULL;
	char mapaHelbidea[MAX_STR];
	int egoera = MENU;
	int *mapaAukera = (int*)malloc(sizeof(int));
	
	do {
		switch (egoera) {
			case MENU:
				egoera = menuMain();
				break;
			case MAPAK:
				egoera = menuMapak(mapaAukera);
				break;
			case SIMULAZIOA:
				if (mapaAukera != NULL && mapaHelbideKargatu(*mapaAukera, mapaHelbidea)) {
					if (mapaKargatu(&mapa, mapaHelbidea)) {
						egoera = simulazioa(mapa);
					}
				}
				break;
			case ITXI:
				break;
			default:
				egoera = ITXI;
				break;
		}
	} while (egoera != ITXI);
	if (mapaAukera != NULL) free(mapaAukera);
	SDL_Quit();
	return 0;
}

void simulazioMugimenduakExekutatu(MAPA mapa, NODO_ERPINA *bidea) {
	NODO_ERPINA* aux = bidea;
	POSIZIOA pos;
	POSIZIOA hurrengoLaukia;
	POSIZIOA mugimenduaPantailan;
	POSIZIOA dest;
	int dist;

	while (aux->ptrHurrengoa != NULL) aux = aux->ptrHurrengoa;
	dest = koordToPos(aux->erpina->koord, mapa.eskala);
	aux = bidea;

	pos = mapanPosizioa(mapa, koordToPos(bidea->erpina->koord, mapa.eskala));
	mugimenduaPantailan = posBiderEskala(pos, mapa.eskala);
	do {
		hurrengoLaukia = koordToPos(bidea->erpina->koord, mapa.eskala);

		do {
			pantailaGarbitu();
			mapaMarraztu(mapa, SIMULAZIO_MAPA_POS);
			menuSimulazioMenuBueltatu(mapa);
			laukiaMarkatu(koordToPos(aux->erpina->koord, mapa.eskala), mapa.eskala);
			laukiaMarkatu(dest, mapa.eskala);
			zirkuluaMarraztu((int)mugimenduaPantailan.x + mapa.eskala / 2, (int)mugimenduaPantailan.y + mapa.eskala / 2, mapa.eskala / 3, 0);
			mugimenduaPantailan = zirkuluaMugitu(mugimenduaPantailan, hurrengoLaukia);
			SDL_RenderDrawLine(getRenderer(), (int)mugimenduaPantailan.x + mapa.eskala / 2, (int)mugimenduaPantailan.y + mapa.eskala / 2, (int)hurrengoLaukia.x + mapa.eskala / 2, (int)hurrengoLaukia.y + mapa.eskala / 2);
			pantailaBerriztu();
			SDL_Delay(5);
			dist = (int)(sqrt(pow((double)hurrengoLaukia.x - mugimenduaPantailan.x, 2) + pow((double)hurrengoLaukia.y - mugimenduaPantailan.y, 2)));
		} while (dist > 0);

		mugimenduaPantailan = koordToPos(bidea->erpina->koord, mapa.eskala);
		bidea = bidea->ptrHurrengoa;
	} while (bidea != NULL && bidea->erpina->dist > 0);
}



int simulazioa(MAPA *mapa) {
	if (simulazioPantaila(*mapa)) {
		NODO_ERPINA* bidea = NULL;
		ERPINA *grafoa;
		KOORD hasiera;
		KOORD helburua;
		int egoera = SIMULAZIOA;
		int ebentu;

		menuSimulazioInstruzioak(mapa);

		pantailaGarbitu();
		mapaMarraztu(*mapa, SIMULAZIO_MAPA_POS);
		menuSimulazioMenuBueltatu(*mapa);
		pantailaBerriztu();

		do {
			ebentu = ebentuaJasoGertatuBada();
			
			if (ebentu == SAGU_BOTOIA_EZKERRA) {
				hasiera = posToKoord(saguarenPosizioa(), mapa->eskala);
				if (mapanLaukiMota(*mapa, hasiera) == ZORUA) {
					pantailaGarbitu();
					mapaMarraztu(*mapa, SIMULAZIO_MAPA_POS);
					laukiaMarkatu(koordToPos(hasiera, mapa->eskala), mapa->eskala);
					menuSimulazioMenuBueltatu(*mapa);
					pantailaBerriztu();
					grafoa = grafoaSortu((*mapa).array, hasiera);
					do {
						bidea = NULL;
						ebentu = ebentuaJasoGertatuBada();
						if (ebentu == SAGU_BOTOIA_EZKERRA) {
							helburua = posToKoord(saguarenPosizioa(), mapa->eskala);
							if (mapanLaukiMota(*mapa, helburua) == ZORUA) {
								bidea = bideLaburrena(grafoa, batKopuruaMapan((mapa)->array), helburua);
								if (bidea != NULL) simulazioMugimenduakExekutatu(*mapa, bidea);
							}
							else ebentu = 0;
						}
					} while (ebentu != SAGU_BOTOIA_EZKERRA || bidea == NULL);
					free(grafoa);
				}
			}
			if (bidea != NULL) {
				menuSimulazioBideErrepikatu(*mapa);
				pantailaBerriztu();
				if (ebentu == TECLA_r) {
					grafoa = grafoaSortu((*mapa).array, helburua);
					bidea = bideLaburrena(grafoa, batKopuruaMapan((mapa)->array), hasiera);
					free(grafoa);
					simulazioMugimenduakExekutatu(*mapa, bidea);
					bidea = NULL;
				}
			}
		} while (egoera == SIMULAZIOA && ebentu != TECLA_ESCAPE);
		free(mapa->array);
		free(mapa);
		sgItxi();
		return MENU;
	}
	else return -1;
}
