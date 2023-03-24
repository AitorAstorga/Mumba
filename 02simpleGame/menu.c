#include "menu.h"
#include "gehigarriak.h"

void menuMainBotoiak(SDL_Rect botoiak[]) {
	botoiak[0].x = SCREEN_WIDTH / 8;
	botoiak[0].y = SCREEN_HEIGHT / 9;
	botoiak[0].w = SCREEN_WIDTH - (SCREEN_WIDTH / 4);
	botoiak[0].h = 3 * (SCREEN_HEIGHT / 9);
	SDL_RenderFillRect(getRenderer(), &botoiak[0]);

	botoiak[1].x = SCREEN_WIDTH / 8;
	botoiak[1].y = 5 * (SCREEN_HEIGHT / 9);
	botoiak[1].w = SCREEN_WIDTH - (SCREEN_WIDTH / 4);
	botoiak[1].h = 3 * (SCREEN_HEIGHT / 9);
	SDL_RenderFillRect(getRenderer(), &botoiak[1]);
}

void menuMainTextuak() {
	textuaGaitu(SCREEN_HEIGHT / 5);
	textuaIdatzi((int)(SCREEN_WIDTH / 3.5), SCREEN_HEIGHT / 6, "MAPAK", 0, (SDL_Color) { 0, 0, 0, 255 });
	textuaIdatzi((int)(SCREEN_WIDTH / 2.8), (int)(SCREEN_HEIGHT - SCREEN_HEIGHT / 2.5), "ITXI", 0, (SDL_Color) { 0, 0, 0, 255 });
}

int menuMain() {
	POSIZIOA pos;
	SDL_Rect *botoiak = (SDL_Rect*)malloc(sizeof(SDL_Rect) * 2);
	int egoera = MENU;
	int ebentu = 0;

	if (sgHasieratu(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) == -1) {
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
		return -1;
	}

	SDL_SetRenderDrawColor(getRenderer(), 255, 255, 255, 255);
	menuMainBotoiak(botoiak);
	menuMainTextuak();
	pantailaBerriztu();

	do {
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == SAGU_BOTOIA_EZKERRA) {
			pos = saguarenPosizioa();
			if (menuMainBotoienBarruanAlDa(botoiak, 2, pos) == 0) {
				egoera = MAPAK;
			}
			else if (menuMainBotoienBarruanAlDa(botoiak, 2, pos) == 1) {
				egoera = ITXI;
			}
		}
	} while (egoera != ITXI && egoera != MAPAK);

	free(botoiak);
	sgItxi();
	return egoera;
}

int menuMapak(int *mapaAukera) {
	MAPA **mapa = (MAPA**)malloc(sizeof(MAPA) * MAX_MAPA);
	POSIZIOA posMapa = { MENU_MAPAK_MARGEN , MENU_MAPAK_MARGEN };
	int ebentu;
	int saguGurpilAbiadura = SAGU_GURPILA_ABIADURA;
	int egoera = MAPAK;
	if (sgHasieratu(750, 600, SDL_WINDOW_SHOWN) == -1) {
		fprintf(stderr, "Ezin da %ix%i bideoa gaitu: %s\n", 750, 600, SDL_GetError());
		//return -1;
	}
	SDL_Rect lauki = MENU_MAPAK_LAUKIAK;
	char mapaHelbide[MAX_STR];
	int mapaKop = 1;
	while (mapaHelbideKargatu(mapaKop, mapaHelbide)) {
		if (mapaKargatu(mapa + mapaKop - 1, mapaHelbide) && mapa != NULL) {
			mapa[mapaKop - 1]->eskala = mapaEskalatu(mapa[mapaKop - 1]->altuera, mapa[mapaKop - 1]->luzera, 200, 300);
		}
		mapaKop++;
	}
	mapaKop--;
	textuaGaitu(SCREEN_HEIGHT / 30);
	do {
		pantailaGarbitu();
		menuMapakLaukiak(lauki, mapaKop, mapa);
		textuaIdatzi(lauki.x, lauki.y - MENU_MAPAK_MARGEN + 10, "Sakatu ESC Menu-ra joateko  --  Klik laukietan mapa aukeratzeko", 0, (SDL_Color) { 255, 255, 255, 255 });
		pantailaBerriztu();
		ebentu = ebentuaJasoGertatuBada();
		if (ebentu == WHEEL_MUGIMENDU_GORA || ebentu == WHEEL_MUGIMENDU_BEHERA) {
			if (ebentu == WHEEL_MUGIMENDU_GORA) {
				lauki.y += saguGurpilAbiadura;
				posMapa.y += saguGurpilAbiadura;
			}
			else if (ebentu == WHEEL_MUGIMENDU_BEHERA) {
				lauki.y -= saguGurpilAbiadura;
				posMapa.y -= saguGurpilAbiadura;
			}
			
		}
		if (ebentu == SAGU_BOTOIA_EZKERRA) {
			if ((*mapaAukera = menuMapakBotoiak(saguarenPosizioa(), lauki, mapaKop)) != -1) {
				egoera = SIMULAZIOA;
			}
		}
		if (ebentu == TECLA_ESCAPE) egoera = MENU;
	} while (egoera == MAPAK);
	free(mapa);
	sgItxi();
	return egoera;
}

int menuMainBotoienBarruanAlDa(SDL_Rect botoiak[], int botoiKop, POSIZIOA pos) {
	for (int i = 0; i < botoiKop; i++) {
		if (pos.x > botoiak[i].x && pos.x < botoiak[i].x + botoiak[i].w) {
			if (pos.y > botoiak[i].y && pos.y < botoiak[i].y + botoiak[i].h) {
				return i;
			}
		}
	}
	return -1;
}

void menuMapakLaukiak(SDL_Rect lauki, int laukiKop, MAPA **mapa) {
	POSIZIOA posMapa;
	for (int i = 0; i < laukiKop; i++) {
		if (i % 2 == 0) {
			lauki.x = MENU_MAPAK_MARGEN;
			if (i > 0) lauki.y += lauki.w - MENU_MAPAK_MARGEN;
		}
		else lauki.x = 2 * MENU_MAPAK_MARGEN + lauki.w;

		posMapa.x = (float)lauki.x;
		posMapa.y = (float)lauki.y;
		mapaMarraztu(**(mapa + i), posMapa);
		SDL_SetRenderDrawColor(getRenderer(), KOLORE_TXURIA);
		SDL_RenderDrawRect(getRenderer(), &lauki);
	}
}

int menuMapakBotoiak(POSIZIOA saguPos, SDL_Rect lauki, int laukiKop) {
	for (int i = 0; i < laukiKop; i++) {
		if (i % 2 == 0) {
			lauki.x = MENU_MAPAK_MARGEN;
			if (i > 0) lauki.y += lauki.w - MENU_MAPAK_MARGEN;
		}
		else lauki.x = 2 * MENU_MAPAK_MARGEN + lauki.w;

		if (saguPos.x > lauki.x&& saguPos.x < lauki.x + lauki.w) {
			if (saguPos.y > lauki.y&& saguPos.y < lauki.y + lauki.h) {
				return i + 1;
			}
		}
	}
	return -1;
}

void menuSimulazioInstruzioak(MAPA* mapa) {
	SDL_Rect instruzioLaukia;
	int textuTamaina = mapa->eskala * mapa->luzera / 29;
	SDL_SetRenderDrawColor(getRenderer(), 20, 20, 20, 50);
	instruzioLaukia.x = 0;
	instruzioLaukia.y = 0;
	instruzioLaukia.w = mapa->luzera * mapa->eskala;
	instruzioLaukia.h = mapa->altuera * mapa->eskala / 2;
	SDL_RenderFillRect(getRenderer(), &instruzioLaukia);
	textuaGaitu(textuTamaina);
	textuaIdatzi(textuTamaina, textuTamaina, "[Instruzioak] - Sakatu 'enter' jarraitzeko", 0, (SDL_Color) { 255, 255, 255, 255 });
	textuaIdatzi(textuTamaina, 3 * textuTamaina, "  1 - Lehenengo klik ezker hasierako posizioa zehazteko", 0, (SDL_Color) { 255, 255, 255, 255 });
	textuaIdatzi(textuTamaina, 6 * textuTamaina, "  2 - Bigarren klik ezker helmuga zehazteko", 0, (SDL_Color) { 255, 255, 255, 255 });
	textuaIdatzi(textuTamaina, 8 * textuTamaina, "      Aukerak:", 0, (SDL_Color) { 255, 255, 255, 255 });
	textuaIdatzi(textuTamaina, 10 * textuTamaina, "         Hasiera posiziora bueltatu", 0, (SDL_Color) { 255, 255, 255, 255 });
	textuaIdatzi(textuTamaina, 12 * textuTamaina, "         Bide berria egin", 0, (SDL_Color) { 255, 255, 255, 255 });
	pantailaBerriztu();
	while (ebentuaJasoGertatuBada() != TECLA_RETURN);
}

void menuSimulazioMenuBueltatu(MAPA mapa) {
	int textuTamaina = (mapa.luzera * mapa.eskala) / 23;
	textuaGaitu(textuTamaina);
	textuaIdatzi(textuTamaina, mapa.altuera * mapa.eskala + textuTamaina, "ESC menu-ra bueltatzeko", 0, (SDL_Color) { 255, 255, 255, 255 });
}

void menuSimulazioBideErrepikatu(MAPA mapa) {
	int textuTamaina = (mapa.luzera * mapa.eskala) / 23;
	textuaGaitu(textuTamaina);
	textuaIdatzi(textuTamaina, mapa.altuera * mapa.eskala + 4 * textuTamaina, "'r' hasierako posiziora bueltatzeko", 0, (SDL_Color) { 255, 255, 255, 255 });
}
