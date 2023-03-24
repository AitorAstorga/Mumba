#include "gehigarriak.h"
#include "graphics.h"

void zirkuluaMarraztu(int x, int y, int radio, int sg) {
	int puntuX;
	int puntuY;

	SDL_SetRenderDrawColor(getRenderer(), 0, 0, 0, 255);

	while (radio > 0) {
		for (int t = 0; t < 360; t++) {
			puntuX = (int)(x + radio * cos(t));
			puntuY = (int)(y + radio * sin(t));
			SDL_RenderDrawPoint(getRenderer(), puntuX, puntuY);
		}
		radio--;
	}
}

POSIZIOA zirkuluaMugitu(POSIZIOA pos1, POSIZIOA pos2) {
	float angelua = atanf((float)(pos2.x - pos1.x) / (pos2.y - pos1.y));
	if (pos2.y - pos1.y < 0) angelua += (float)PI;
	pos1.x += sinf(angelua);
	pos1.y += cosf(angelua);
	return pos1;
}

POSIZIOA koordToPos(KOORD koord, int eskala) {
	POSIZIOA emaitza;
	emaitza.x = (float)(koord.zutabe * eskala);
	emaitza.y = (float)(koord.ilara * eskala);
	return emaitza;
}

KOORD posToKoord(POSIZIOA pos, int eskala) {
	KOORD emaitza;
	emaitza.zutabe = (int)(pos.x / eskala);
	emaitza.ilara = (int)(pos.y / eskala);
	return emaitza;
}

POSIZIOA posBiderEskala(POSIZIOA pos, int eskala) {
	pos.x *= eskala;
	pos.y *= eskala;
	return pos;
}
