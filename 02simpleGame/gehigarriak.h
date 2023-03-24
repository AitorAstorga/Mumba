#ifndef GEHIGARRIAK_H
#define GEHIGARRIAK_H

#include "ebentoak.h"
#include "mapa.h"

#define PI 3.14159265
#define MAX_STR 128

void zirkuluaMarraztu(int x, int y, int radio, int sg);

//Posiziotik helburura (float) 0 - 1 hurbilago POSIZIOA bueltatzen du (while erabili)
POSIZIOA zirkuluaMugitu(POSIZIOA pos1, POSIZIOA pos2);

//input: KOORD, output: POSIZIOA
POSIZIOA koordToPos(KOORD koord, int eskala);

//input: POSIZIOA, output: KOORD
KOORD posToKoord(POSIZIOA pos, int eskala);

//input: POSIZIOA(koord), output: POSIZIOA
POSIZIOA posBiderEskala(POSIZIOA pos, int eskala);

#endif
