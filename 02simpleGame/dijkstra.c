#include "dijkstra.h"
#include "gehigarriak.h"

int batKopuruaMapan(int *mapa) {
	int batKop = 0;

	for (int i = 0; i < MAPA_DIM; i++) {
		for (int j = 0; j < MAPA_DIM; j++) {
			if (*(mapa + i * MAPA_DIM + j) == 1) {
				batKop++;
			}
		}
	}

	return batKop;
}

ERPINA* erpinBerria(ERPINA datuak) {
	ERPINA *berria = (ERPINA*)malloc(sizeof(ERPINA));
	if (berria != NULL) *berria = datuak;
	return berria;
}

void erpinaSartuHasieran(NODO_ERPINA **pila, ERPINA *berria) {
	NODO_ERPINA *nodoBerria = (NODO_ERPINA*)malloc(sizeof(NODO_ERPINA));
	NODO_ERPINA *aux = *pila;

	if (nodoBerria != NULL) {
		nodoBerria->erpina = berria;
		nodoBerria->ptrAurrekoa = NULL;
	}
	if (*pila == NULL) *pila = nodoBerria;
	else {
		while (aux->ptrAurrekoa != NULL) {
			aux = aux->ptrAurrekoa;
		}
		aux->ptrAurrekoa = nodoBerria;
	}
}

int erpinAdjazenteak(int nodoKop, ERPINA *nodoak, ERPINA *nodo) {
	int adjacentKop = 0;

	for (int id = 0; id < nodoKop; id++) {
		if (nodoak[id].koord.zutabe == nodo->koord.zutabe) {//Eje y
			if (nodo->koord.ilara + 1 == nodoak[id].koord.ilara) {//Behean
				nodo->adyazenteak[adjacentKop] = id;
				adjacentKop++;
			}
			if (nodo->koord.ilara - 1 == nodoak[id].koord.ilara) {//Goian
				nodo->adyazenteak[adjacentKop] = id;
				adjacentKop++;
			}
		}
		if (nodoak[id].koord.ilara == nodo->koord.ilara) {//Eje x
			if (nodo->koord.zutabe + 1 == nodoak[id].koord.zutabe) {//Eskuinean
				nodo->adyazenteak[adjacentKop] = id;
				adjacentKop++;
			}
			if (nodo->koord.zutabe - 1 == nodoak[id].koord.zutabe) {//Ezkerrean
				nodo->adyazenteak[adjacentKop] = id;
				adjacentKop++;
			}
		}
	}

	return adjacentKop;
}

void erpinakHasieratu(int *mapa, ERPINA *nodoak) {
	int bat = 0;
	for (int i = 0; i < MAPA_DIM; i++) {
		for (int j = 0; j < MAPA_DIM; j++) {
			if (*(mapa + i * MAPA_DIM + j) == 1) {
				(nodoak + bat)->dist = INFINITO;
				(nodoak + bat)->koord.ilara = i;
				(nodoak + bat)->koord.zutabe = j;
				(nodoak + bat)->id = bat;
				bat++;
			}
		}
	}
}

int posizioarenId(ERPINA *nodoak, int nodoKop, KOORD pos) {
	int id = -1;
	for (int i = 0; i < nodoKop; i++) {
		if (nodoak[i].koord.ilara == pos.ilara && nodoak[i].koord.zutabe == pos.zutabe) {
			id = i;
		}
	}
	return id;
}

NODO_ERPINA* bideLaburrena(ERPINA *erpinak, int erpinKop, KOORD posDest) {
	NODO_ERPINA *bidea = NULL;
	int bukaera = posizioarenId(erpinak, erpinKop, posDest);
	int bideNodoKop = 0;
	NODO_ERPINA *kursorAux = NULL;
	NODO_ERPINA *aux = NULL;

	ERPINA *berria = erpinBerria(erpinak[bukaera]);
	erpinaSartuHasieran(&bidea, berria);
	bidea->ptrHurrengoa = NULL;
	if (berria->dist == 0) return bidea;//Hasiera eta bukaera puntu berdina
	if (berria->aurrekoId < 0) return NULL;//Hasieratik ezinezkoa da bukaerara joatea
	do {
		berria = erpinBerria(erpinak[berria->aurrekoId]);
		erpinaSartuHasieran(&bidea, berria);
		bideNodoKop++;
		kursorAux = bidea;
		aux = bidea;
		for (int i = 0; i < bideNodoKop; i++) {
			kursorAux = kursorAux->ptrAurrekoa;
		}
		for (int i = 0; i < bideNodoKop - 1; i++) {
			aux = aux->ptrAurrekoa;
		}
		kursorAux->ptrHurrengoa = aux;

	} while (berria->dist > 0);
	
	while (bidea->erpina->dist > 0) bidea = bidea->ptrAurrekoa;
	return bidea;
}

int erpinaAztertuAlDa(ERPINA erpina, int *aztertuak, int aztertuKop) {
	int aztertuDa = 0;
	for (int j = 0; j < aztertuKop; j++) {
		if (erpina.id == aztertuak[j]) {
			aztertuDa = 1;
		}
	}
	return aztertuDa;
}

ERPINA* grafoaSortu(int *mapaArray, KOORD posIni) {
	int batKop = batKopuruaMapan(mapaArray);

	//Nodo guztien zerrenda (bat puntuak mapan)
	ERPINA *erpinak = (ERPINA*)malloc(sizeof(ERPINA) * batKop);
	//id aztertuen zerrenda
	int *aztertuak = (int*)malloc(sizeof(int) * batKop);
	int aztertuKop = 0;
	
	//HASIERATU erpinak
	erpinakHasieratu(mapaArray, erpinak);
	int hasiera = posizioarenId(erpinak, batKop, posIni);
	erpinak[hasiera].dist = 0;

	//Nodoak aztertzeko erabiliko dugun pibot-a
	ERPINA pibot = erpinak[hasiera];

	while (aztertuKop < batKop) {		
		pibot.adjazenteKop = erpinAdjazenteak(batKop, erpinak, &pibot);
		
		aztertuak[aztertuKop] = pibot.id;
		aztertuKop++;
		
		erpinak[pibot.id] = pibot;

		//Nodo guztien distantzien aktualizazioa
		//recorro todos los puntos
		//comparo la distancia de cada punto + 1 con la distancia de sus adjacentes
			//si la primera es menor, sustituyo la distancia y pAnterior del adjacente comparado

		for (int i = 0; i < aztertuKop; i++) {
			for (int j = 0; j < erpinak[aztertuak[i]].adjazenteKop; j++) {
				if (erpinak[aztertuak[i]].dist + 1 < erpinak[erpinak[aztertuak[i]].adyazenteak[j]].dist) {
					erpinak[erpinak[aztertuak[i]].adyazenteak[j]].dist = erpinak[aztertuak[i]].dist + 1;
					erpinak[erpinak[aztertuak[i]].adyazenteak[j]].aurrekoId = erpinak[aztertuak[i]].id;
				}
			}
		}
		
		//Adjazente txikienaren bilaketa
		int adjazenteTxikiena = INFINITO;

		for (int i = 0; i < batKop; i++) {
			if (erpinaAztertuAlDa(erpinak[i], aztertuak, aztertuKop) == 0) {
				if (erpinak[i].dist < adjazenteTxikiena) {
					adjazenteTxikiena = erpinak[i].id;
				}
			}
		}

		if (adjazenteTxikiena != INFINITO) {
			pibot = erpinak[adjazenteTxikiena];
		}
	}
	
	return erpinak;
}