#include "tablero.h"
#include "utilidades.h"
#include <iostream>

using namespace std;

void inicializarTablero(char tablero[TAMANO][TAMANO]) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 4) tablero[i][j] = NEGRA;
                else if (i > 5) tablero[i][j] = BLANCA;
                else tablero[i][j] = VACIO;
            } else {
                tablero[i][j] = VACIO;
            }
        }
    }
}

void mostrarTablero(char tablero[TAMANO][TAMANO]) {
    limpiarPantalla();
    cout << "\n    ";
    for (int j = 0; j < TAMANO; j++) {
        cout << j << "   ";
    }
    cout << "\n";
    
    for (int i = 0; i < TAMANO; i++) {
        cout << i << " | ";
        for (int j = 0; j < TAMANO; j++) {
            cout << tablero[i][j] << " | ";
        }
        cout << "\n";
    }
}

char obtenerPieza(char tablero[TAMANO][TAMANO], int fila, int col) {
    if (esPosicionValida(fila, col)) {
        return tablero[fila][col];
    }
    return VACIO;
}

void colocarPieza(char tablero[TAMANO][TAMANO], int fila, int col, char pieza) {
    if (esPosicionValida(fila, col)) {
        tablero[fila][col] = pieza;
    }
}

void eliminarPieza(char tablero[TAMANO][TAMANO], int fila, int col) {
    if (esPosicionValida(fila, col)) {
        tablero[fila][col] = VACIO;
    }
}

void coronar(char tablero[TAMANO][TAMANO], int fila, int col) {
    if (tablero[fila][col] == BLANCA && fila == 0) {
        tablero[fila][col] = DAMA_BLANCA;
    }
    if (tablero[fila][col] == NEGRA && fila == TAMANO - 1) {
        tablero[fila][col] = DAMA_NEGRA;
    }
}

bool verificarVictoria(char tablero[TAMANO][TAMANO]) {
    bool blancas = false, negras = false;
    
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            if (tablero[i][j] == BLANCA || tablero[i][j] == DAMA_BLANCA) {
                blancas = true;
            }
            if (tablero[i][j] == NEGRA || tablero[i][j] == DAMA_NEGRA) {
                negras = true;
            }
        }
    }

    if (!blancas) {
        cout << "\n¡Ganan las negras!\n";
        return true;
    }
    if (!negras) {
        cout << "\n¡Ganan las blancas!\n";
        return true;
    }
    return false;
}

bool esPosicionValida(int fila, int col) {
    return fila >= 0 && fila < TAMANO && col >= 0 && col < TAMANO;
}