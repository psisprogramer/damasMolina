#ifndef JUEGO_H
#define JUEGO_H

#include <string>

int leerEnteroSeguro(std::string mensaje);
void pausarConEnter();
void configurarJugadores();
void mostrarReglas();
void jugarPartida();
void mostrarMenu();

extern std::string jugador1;
extern std::string jugador2;

#endif
