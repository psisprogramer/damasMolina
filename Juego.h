
#ifndef JUEGO_HPP
#define JUEGO_HPP

#include "tablero.h"
#include "jugador.h"

// Variables globales del juego
extern char tableroJuego[TAMANO][TAMANO];
extern Jugador jugador1;
extern Jugador jugador2;
extern int jugadorActual;
extern bool juegoActivo;

// Funciones del juego
void configurarJugadores();
void iniciarJuego();
bool ejecutarTurno();
void mostrarMenu();
int leerEntrada(const char* mensaje);

#endif // JUEGO_HPP