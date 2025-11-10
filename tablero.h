#ifndef TABLERO_H
#define TABLERO_H

#include <string>

#define RESET   "\033[0m"
#define BG_DARK "\033[100m"
#define BG_LIGHT "\033[47m"
#define C_AZUL  "\033[36m"
#define C_ROJO  "\033[31m"
#define C_VERDE "\033[32m"
#define C_AMAR  "\033[33m"

extern int TAMANO;
extern char VACIO;
extern char BLANCA;
extern char NEGRA;
extern char DAMA_BLANCA;
extern char DAMA_NEGRA;
extern char tablero[20][20];

void inicializarTablero();
void mostrarTablero();
std::string simboloDe(char pieza);
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
bool verificarVictoriaYMostrar(int jugadorActual, const std::string &nombreJugador1, const std::string &nombreJugador2);
void limpiarPantalla();

#endif
