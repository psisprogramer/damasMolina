#include "movimiento.h"
#include <cmath>
#include <iostream>
#include "Tablero.h"

using namespace std;

bool esMovimientoSimpleValido(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador) {
    if (!esPosicionValida(f2, c2) || obtenerPieza(tablero, f2, c2) != VACIO) {
        return false;
    }

    int deltaFila = f2 - f1;
    int deltaCol = abs(c2 - c1);

    char pieza = obtenerPieza(tablero, f1, c1);
    
    if (pieza == BLANCA && jugador == 1 && deltaFila != -1) {
        return false;
    }
    if (pieza == NEGRA && jugador == 2 && deltaFila != 1) {
        return false;
    }

    return deltaCol == 1 && abs(deltaFila) == 1;
}

bool esCaptura(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador, int &filaComida, int &colComida) {
    if (!esPosicionValida(f2, c2) || obtenerPieza(tablero, f2, c2) != VACIO) {
        return false;
    }

    int deltaFila = f2 - f1;
    int deltaCol = c2 - c1;

    if (abs(deltaFila) != 2 || abs(deltaCol) != 2) {
        return false;
    }

    int filaInter = f1 + deltaFila / 2;
    int colInter = c1 + deltaCol / 2;
    char piezaIntermedia = obtenerPieza(tablero, filaInter, colInter);

    if (piezaIntermedia == VACIO) {
        return false;
    }
    
    if (jugador == 1 && (piezaIntermedia == NEGRA || piezaIntermedia == DAMA_NEGRA)) {
        filaComida = filaInter;
        colComida = colInter;
        return true;
    }
    if (jugador == 2 && (piezaIntermedia == BLANCA || piezaIntermedia == DAMA_BLANCA)) {
        filaComida = filaInter;
        colComida = colInter;
        return true;
    }

    return false;
}

bool puedeCapturarDesde(char tablero[TAMANO][TAMANO], int f, int c, int jugador) {
    int filaComida, colComida;
    int movimientos[4][2] = { {-2, -2}, {-2, 2}, {2, -2}, {2, 2} };

    for (int i = 0; i < 4; i++) {
        int f2 = f + movimientos[i][0];
        int c2 = c + movimientos[i][1];
        if (esCaptura(tablero, f, c, f2, c2, jugador, filaComida, colComida)) {
            return true;
        }
    }
    return false;
}

void realizarMovimiento(char tablero[TAMANO][TAMANO], int f1, int c1, int f2, int c2, int jugador) {
    int filaComida = -1, colComida = -1;
    bool captura = esCaptura(tablero, f1, c1, f2, c2, jugador, filaComida, colComida);

    char pieza = obtenerPieza(tablero, f1, c1);
    colocarPieza(tablero, f2, c2, pieza);
    eliminarPieza(tablero, f1, c1);

    if (captura) {
        eliminarPieza(tablero, filaComida, colComida);
        coronar(tablero, f2, c2);
        mostrarTablero(tablero);

        // Captura múltiple
        if (puedeCapturarDesde(tablero, f2, c2, jugador)) {
            cout << "\nPuedes seguir capturando con la misma pieza.\n";
            int nf, nc;
            cout << "Nueva fila destino: ";
            cin >> nf;
            cout << "Nueva columna destino: ";
            cin >> nc;
            realizarMovimiento(tablero, f2, c2, nf, nc, jugador);
        }
    } else {
        coronar(tablero, f2, c2);
    }
}