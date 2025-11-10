#ifndef TABLERO_HPP
#define TABLERO_HPP

const int TAMANO = 10;
const char VACIO = '.';
const char BLANCA = 'b';
const char NEGRA = 'n';
const char DAMA_BLANCA = 'B';
const char DAMA_NEGRA = 'N';

// Funciones del tablero
void inicializarTablero(char tablero[TAMANO][TAMANO]);
void mostrarTablero(char tablero[TAMANO][TAMANO]);
char obtenerPieza(char tablero[TAMANO][TAMANO], int fila, int col);
void colocarPieza(char tablero[TAMANO][TAMANO], int fila, int col, char pieza);
void eliminarPieza(char tablero[TAMANO][TAMANO], int fila, int col);
void coronar(char tablero[TAMANO][TAMANO], int fila, int col);
bool verificarVictoria(char tablero[TAMANO][TAMANO]);
bool esPosicionValida(int fila, int col);

#endif // TABLERO_HPP