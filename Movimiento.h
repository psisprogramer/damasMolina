
#ifndef MOVIMIENTO_HPP
#define MOVIMIENTO_HPP

#include "tablero.h"

// Funciones de movimiento
bool esMovimientoSimpleValido(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador);
bool esCaptura(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador, int &filaComida, int &colComida);
bool puedeCapturarDesde(char tablero[TAMANO][TAMANO], int f, int c, int jugador);
void realizarMovimiento(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador);

#endif // MOVIMIENTO_HPP