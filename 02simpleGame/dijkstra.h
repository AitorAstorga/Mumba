#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <limits.h> 
#include <stdio.h> 
#include "mapa.h"

#define INFINITO INT_MAX

typedef struct erpina {
	KOORD koord; 
	int adyazenteak[8];
	int adjazenteKop;
	int id;
	int dist;
	int aurrekoId;
} ERPINA;

typedef struct nodo_erpina {
	ERPINA* erpina;
	struct nodo_erpina* ptrHurrengoa;
	struct nodo_erpina* ptrAurrekoa;
} NODO_ERPINA;

//Mapa baten dauden 1 edo zoru-lauki kopurua | (int)
int batKopuruaMapan(int *mapa);

//Nodo berria sortzeko input-ak | (VERTICE*)
ERPINA* erpinBerria(ERPINA datuak);

//Nodo bat kate baten hasieran sartu | (void)
void erpinaSartuHasieran(NODO_ERPINA **pila, ERPINA *berria);

//Nodo baten nodo adjazenteak kalkulatu eta haien kopurua bueltatu | (int)
int erpinAdjazenteak(int nodoKop, ERPINA *nodoak, ERPINA *nodo);

//Nodoak hasieratu. Mapan dauden puntu guztiak, berdin 1 direnak hartzen dira. | (void)
void erpinakHasieratu(int *mapa, ERPINA *nodoak);

//Mapan aukeratutako lauki baten id-a
int posizioarenId(ERPINA *nodoak, int nodoKop, KOORD pos);

//Bide laburrenaren zerrenda kateatua
NODO_ERPINA* bideLaburrena(ERPINA *nodoak, int nodoKop, KOORD posDest);

//Grafoa sortzean aztertu bada 1 bueltatu, ez bada aztertu 0
int erpinaAztertuAlDa(ERPINA erpina, int *aztertuak, int aztertuKop);

//Puntu batera joateko kostuen grafoa
ERPINA* grafoaSortu(int *mapaArray, KOORD posIni);

#endif