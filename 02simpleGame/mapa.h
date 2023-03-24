#ifndef MAPA_H
#define MAPA_H

#include "ebentoak.h"

#define MAPA_FITX "./mapak/MAPA"

#define MAPA_DIM 300
#define SIMULAZIO_MARGEN 200
#define SIMULAZIO_MAPA_POS (POSIZIOA){ 0, 0 }

#define KOLORE_MARROIA 128, 64, 0, 0
#define KOLORE_TXURIA 255, 255, 255, 255
#define KOLORE_BELTZA 0, 0, 0, 255
#define KOLORE_BERDEA 0, 255, 0, 255

typedef enum lauki_mota { PARETA, ZORUA, VOID = -16} LAUKI_MOTA;//-16 oso ezpezifikoa delako debug-an ikusteko

typedef struct mapa {
	int *array;
	int altuera;
	int luzera;
	int eskala;
} MAPA;

typedef struct koord {
	int ilara;
	int zutabe;
} KOORD;

//(MAPA** mapa) aldagaian (char *mapaHelbide) izeneko fitxategi batetik datuak kargatu
//Informazio gehiago: mapa.c
int mapaKargatu(MAPA **mapa, char *mapaHelbide);

//Kargatutako mapa bat simulazio leihoan bistaratzeko dimentsio egokiak kalkulatu lauki bakoitzeko
int mapaEskalatu(int ilaraKop, int zutabeKop, int canvasAltuera, int canvasLuzera);

//Simulazioa pantailaratzeko behar den leihoa ireki
int simulazioPantaila(MAPA mapa);

//Kargatutako mapa bat pantailaratu
int mapaMarraztu(MAPA mapa, POSIZIOA pos);

//Pantailaratu den mapa batean pixel-posizio zehatz bat mapa-koordenatuera bihurtu
POSIZIOA mapanPosizioa(MAPA mapa, POSIZIOA posPantaila);

//Maparen id-aren arabera helbidearen izena sortu (MAPA_FITX%i.txt)
int mapaHelbideKargatu(int mapaZenb, char *emaitza);

//Mapan lauki bat berdez marraztu
void laukiaMarkatu(POSIZIOA laukia, int eskala);

//Mapan lauki bat ZORUA, PARETA edo VOID bueltatu
LAUKI_MOTA mapanLaukiMota(MAPA mapa, KOORD koord);

#endif
