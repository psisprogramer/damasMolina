#include "ficha.h"
#include "tablero.h"
#include <iostream>
#include <cstdlib>
#include <cmath>

bool posicionValida(int f, int c) {
    return f >= 0 && f < TAMANO && c >= 0 && c < TAMANO;
}

bool esPiezaJugador(int jugador, char pieza) {
    if (jugador == 1) return (pieza == BLANCA || pieza == DAMA_BLANCA);
    return (pieza == NEGRA || pieza == DAMA_NEGRA);
}

bool esDama(char pieza) {
    return pieza == DAMA_BLANCA || pieza == DAMA_NEGRA;
}

bool esCapturaMano(int f1, int c1, int f2, int c2, int jugador, int &fc, int &cc) {
    if (!posicionValida(f2, c2)) return false;
    if (tablero[f2][c2] != VACIO) return false;
    int df = f2 - f1, dc = c2 - c1;
    if (abs(df) != 2 || abs(dc) != 2) return false;
    int fm = f1 + df / 2, cm = c1 + dc / 2;
    char medio = tablero[fm][cm];
    if (medio == VACIO) return false;
    if (jugador == 1 && (medio == NEGRA || medio == DAMA_NEGRA)) { fc = fm; cc = cm; return true; }
    if (jugador == 2 && (medio == BLANCA || medio == DAMA_BLANCA)) { fc = fm; cc = cm; return true; }
    return false;
}

bool esCapturaDama(int f1, int c1, int f2, int c2, int jugador, int &fc, int &cc) {
    if (!posicionValida(f2, c2)) return false;
    if (tablero[f2][c2] != VACIO) return false;
    int df = f2 - f1, dc = c2 - c1;
    if (abs(df) != abs(dc)) return false;
    int dirF = (df > 0) ? 1 : -1;
    int dirC = (dc > 0) ? 1 : -1;
    int enemigos = 0;
    int fEn = -1, cEn = -1;
    for (int k = 1; k < abs(df); k++) {
        int rr = f1 + k * dirF, ccpos = c1 + k * dirC;
        if (tablero[rr][ccpos] != VACIO) {
            if (esPiezaJugador(jugador, tablero[rr][ccpos])) return false;
            enemigos++;
            fEn = rr; cEn = ccpos;
            if (enemigos > 1) return false;
        }
    }
    if (enemigos == 1) {
        if (jugador == 1 && (tablero[fEn][cEn] == NEGRA || tablero[fEn][cEn] == DAMA_NEGRA)) { fc = fEn; cc = cEn; return true; }
        if (jugador == 2 && (tablero[fEn][cEn] == BLANCA || tablero[fEn][cEn] == DAMA_BLANCA)) { fc = fEn; cc = cEn; return true; }
    }
    return false;
}

bool esMovimientoSimple(int f1, int c1, int f2, int c2, int jugador) {
    if (!posicionValida(f2, c2)) return false;
    if (tablero[f2][c2] != VACIO) return false;
    char pieza = tablero[f1][c1];
    int df = f2 - f1, dc = c2 - c1;
    if (esDama(pieza)) {
        if (abs(df) != abs(dc)) return false;
        int dirF = (df > 0) ? 1 : -1;
        int dirC = (dc > 0) ? 1 : -1;
        for (int k = 1; k < abs(df); k++) {
            if (tablero[f1 + k * dirF][c1 + k * dirC] != VACIO) return false;
        }
        return true;
    } else {
        if (abs(df) != 1 || abs(dc) != 1) return false;
        if ((jugador == 1 && df != -1) || (jugador == 2 && df != 1)) return false;
        return true;
    }
}

bool piezaTieneCaptura(int f, int c, int jugador) {
    char pieza = tablero[f][c];
    int fc, cc;
    if (esDama(pieza)) {
        int dirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for (int d = 0; d < 4; d++) {
            int rr = f + dirs[d][0], ccpos = c + dirs[d][1];
            while (posicionValida(rr, ccpos)) {
                if (esCapturaDama(f, c, rr, ccpos, jugador, fc, cc)) return true;
                rr += dirs[d][0]; ccpos += dirs[d][1];
            }
        }
        return false;
    } else {
        int saltos[4][2] = {{2,2},{2,-2},{-2,2},{-2,-2}};
        for (int s = 0; s < 4; s++) {
            if (esCapturaMano(f, c, f + saltos[s][0], c + saltos[s][1], jugador, fc, cc)) return true;
        }
        return false;
    }
}

bool hayCapturaDisponible(int jugador) {
    for (int i = 0; i < TAMANO; i++)
        for (int j = 0; j < TAMANO; j++)
            if (esPiezaJugador(jugador, tablero[i][j]) && piezaTieneCaptura(i, j, jugador))
                return true;
    return false;
}

int contarPiezas(int jugador) {
    int cont = 0;
    for (int i = 0; i < TAMANO; i++)
        for (int j = 0; j < TAMANO; j++)
            if (esPiezaJugador(jugador, tablero[i][j])) cont++;
    return cont;
}