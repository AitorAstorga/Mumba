#include "mapa.h"
#include "gehigarriak.h"
#include <stdio.h>
#include <string.h>
#include "graphics.h"

/*txt formatuan dagoen fitxategi batetik karaktereak irakurtzen ditu fitxategia bukatu arte ('\0').
'0' eta '1' array bidimensional batean gordetzen ditu, '\n' array-an orientatzeko erabiltzen du.
Maparen dimentsioak gordetzen ditu ere. Bere bukaera aukerak:
	1 - SUCCESS.
	0 - ERROR, fitxategia irekitzen.
	(int)char - ERROR, karaktere desegokia txt-an.*/

int mapaKargatu(MAPA **mapa, char *mapaHelbide) {
	FILE *mapaFitx;
	char karak;
	int ilara = 0, zutabe = 0;
	if((*mapa = (MAPA*)malloc(sizeof(MAPA))) == NULL) return -1;
	if(((*mapa)->array = (int*)malloc(sizeof(int) * MAPA_DIM * MAPA_DIM)) == NULL) return -1;
	mapaFitx = fopen(mapaHelbide, "r");
	if (mapaFitx == NULL) return 0;
	else {
		do {
			karak = fgetc(mapaFitx);
			if (karak == '\r') karak = fgetc(mapaFitx);
			if (karak == '1' || karak == '0' || karak == '\n' || karak == ' ') {
				if (karak == '\n') {
					ilara++;
					if (zutabe > (*mapa)->luzera) (*mapa)->luzera = zutabe;
					zutabe = 0;
				}
				else {
					*((*mapa)->array + ilara * MAPA_DIM + zutabe) = karak - '0';
					zutabe++;
				}
			}
			else if (feof(mapaFitx)) {
				(*mapa)->altuera = ++ilara;
				if (zutabe > (*mapa)->luzera) (*mapa)->luzera = ++zutabe;
				(*mapa)->eskala = mapaEskalatu((*mapa)->altuera, (*mapa)->luzera, SCREEN_HEIGHT - SIMULAZIO_MARGEN, SCREEN_WIDTH);
				fclose(mapaFitx);
				return 1;
			}
			else {
				fclose(mapaFitx);
				return karak;
			}
		} while (feof(mapaFitx) == 0);
	}
	fclose(mapaFitx);
	return 0;
}

int mapaEskalatu(int ilaraKop, int zutabeKop, int canvasAltuera, int canvasLuzera) {
	int eskala;

	if (ilaraKop > zutabeKop) {
		eskala = (int)(canvasAltuera / zutabeKop);
		if (eskala * ilaraKop > canvasLuzera) eskala = (int)(canvasLuzera / ilaraKop);
	}
	else {
		eskala = (int)(canvasLuzera / ilaraKop);
		if (eskala * zutabeKop > canvasAltuera) eskala = (int)(canvasAltuera / zutabeKop);
	}

	return eskala;
}

int simulazioPantaila(MAPA mapa) {
	int pantailaX = mapa.luzera * mapa.eskala;
	int pantailaY = mapa.altuera * mapa.eskala + SIMULAZIO_MARGEN;

	if (sgHasieratu(pantailaX, pantailaY, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS) == -1) {
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", pantailaX, pantailaY, SDL_GetError());
		return -1;
	}
	else return 1;
}

int mapaMarraztu(MAPA mapa, POSIZIOA pos) {
	SDL_Rect zuzena;
	int ilaraKop = mapa.luzera;
	int zutabeKop = mapa.altuera;

	for (int zutabe = 0; zutabe <= zutabeKop; zutabe++) {
		for (int ilara = 0; ilara <= ilaraKop; ilara++) {
			if (*(mapa.array + zutabe * MAPA_DIM + ilara) == 0) {
				SDL_SetRenderDrawColor(getRenderer(), KOLORE_TXURIA);
			}
			else if (*(mapa.array + zutabe * MAPA_DIM + ilara) == 1) {
				SDL_SetRenderDrawColor(getRenderer(), KOLORE_MARROIA);
			}
			else SDL_SetRenderDrawColor(getRenderer(), KOLORE_BELTZA);

			zuzena.x = (int)pos.x + ilara * mapa.eskala;
			zuzena.y = (int)pos.y + zutabe * mapa.eskala;
			zuzena.w = zuzena.h = mapa.eskala;
			SDL_RenderFillRect(getRenderer(), &zuzena);
		}
	}
	return 1;
}

POSIZIOA mapanPosizioa(MAPA mapa, POSIZIOA posPantaila) {
	POSIZIOA posMapa;
	posMapa.x = (posPantaila.x / mapa.eskala);
	posMapa.y = (posPantaila.y / mapa.eskala);
	return posMapa;
}

int mapaHelbideKargatu(int mapaZenb, char *helbide) {
	FILE* mapaFitx;
	char mapaHelbide[MAX_STR];
	char mapaHelbideZenb[MAX_STR];
	strncpy(mapaHelbide, MAPA_FITX, MAX_STR);
	snprintf(mapaHelbideZenb, MAX_STR, "%i.txt", mapaZenb);
	strcat(mapaHelbide, mapaHelbideZenb);
	mapaFitx = fopen(mapaHelbide, "r");
	if (mapaFitx != NULL) {
		fclose(mapaFitx);
		strcpy(helbide, mapaHelbide);
		return 1;
	}
	else return 0;
}

void laukiaMarkatu(POSIZIOA laukia, int eskala) {
	SDL_Rect zuzena;
	SDL_SetRenderDrawColor(getRenderer(), KOLORE_BERDEA);
	zuzena.x = (int)laukia.x;
	zuzena.y = (int)laukia.y;
	zuzena.w = zuzena.h = eskala;
	SDL_RenderFillRect(getRenderer(), &zuzena);
}

LAUKI_MOTA mapanLaukiMota(MAPA mapa, KOORD koord) {
	return *(mapa.array + koord.ilara * MAPA_DIM + koord.zutabe);
}
