#ifndef FICHA_H
#define FICHA_H

#include <string>

extern int TAMANO;
extern char VACIO, BLANCA, NEGRA, DAMA_BLANCA, DAMA_NEGRA;
extern char tablero[20][20];

bool posicionValida(int f, int c);
bool esPiezaJugador(int jugador, char pieza);
bool esDama(char pieza);
bool esCapturaMano(int f1, int c1, int f2, int c2, int jugador, int &fc, int &cc);
bool esCapturaDama(int f1, int c1, int f2, int c2, int jugador, int &fc, int &cc);
bool esMovimientoSimple(int f1, int c1, int f2, int c2, int jugador);
bool piezaTieneCaptura(int f, int c, int jugador);
bool hayCapturaDisponible(int jugador);
bool realizarMovimiento(int f1, int c1, int f2, int c2, int jugador);
bool jugadorTieneMovimientos(int jugador);
int contarPiezas(int jugador);

#endif