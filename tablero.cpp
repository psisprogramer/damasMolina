#include "tablero.h"
#include <iostream>
#include <cstdlib>

int TAMANO = 10;
char VACIO = '.';
char BLANCA = 'b';
char NEGRA = 'n';
char DAMA_BLANCA = 'B';
char DAMA_NEGRA = 'N';
char tablero[20][20];

void inicializarTablero() {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            if ((i + j) % 2 == 1) {
                if (i < 4) tablero[i][j] = NEGRA;
                else if (i > 5) tablero[i][j] = BLANCA;
                else tablero[i][j] = VACIO;
            } else tablero[i][j] = VACIO;
        }
    }
}

std::string simboloDe(char pieza) {
    if (pieza == BLANCA) return "b";
    if (pieza == NEGRA) return "n";
    if (pieza == DAMA_BLANCA) return "B";
    if (pieza == DAMA_NEGRA) return "N";
    return " ";
}

void mostrarTablero() {
    std::cout << std::endl;
    std::cout << "   " << C_AMAR;
    for (int j = 0; j < TAMANO; j++) {
        std::cout << " " << j << " ";
    }
    std::cout << RESET << std::endl;
    for (int i = 0; i < TAMANO; i++) {
        std::cout << C_AMAR << " " << i << " " << RESET;
        for (int j = 0; j < TAMANO; j++) {
            bool oscuro = ((i + j) % 2 == 1);
            std::string fondo = oscuro ? BG_DARK : BG_LIGHT;
            std::cout << fondo << " " << simboloDe(tablero[i][j]) << " " << RESET;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Leyenda: b=blanca  n=negra  B=dama blanca  N=dama negra" << std::endl;
}
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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
    int df = f2 - f1;
    int dc = c2 - c1;
    if (abs(df) != 2 || abs(dc) != 2) return false;
    int fm = f1 + df / 2;
    int cm = c1 + dc / 2;
    char medio = tablero[fm][cm];
    if (medio == VACIO) return false;
    if (jugador == 1 && (medio == NEGRA || medio == DAMA_NEGRA)) { fc = fm; cc = cm; return true; }
    if (jugador == 2 && (medio == BLANCA || medio == DAMA_BLANCA)) { fc = fm; cc = cm; return true; }
    return false;
}

bool esCapturaDama(int f1, int c1, int f2, int c2, int jugador, int &fc, int &cc) {
    if (!posicionValida(f2, c2)) return false;
    if (tablero[f2][c2] != VACIO) return false;
    int df = f2 - f1;
    int dc = c2 - c1;
    if (abs(df) != abs(dc)) return false;
    int dirF = (df > 0) ? 1 : -1;
    int dirC = (dc > 0) ? 1 : -1;
    int enemigos = 0;
    int fEn = -1, cEn = -1;
    int pasos = abs(df);
    for (int k = 1; k < pasos; k++) {
        int rr = f1 + k * dirF;
        int ccpos = c1 + k * dirC;
        if (tablero[rr][ccpos] != VACIO) {
            char pk = tablero[rr][ccpos];
            if (esPiezaJugador(jugador, pk)) return false;
            enemigos++;
            fEn = rr; cEn = ccpos;
            if (enemigos > 1) return false;
        }
    }
    if (enemigos == 1) {
        char enemigo = tablero[fEn][cEn];
        if (jugador == 1 && (enemigo == NEGRA || enemigo == DAMA_NEGRA)) { fc = fEn; cc = cEn; return true; }
        if (jugador == 2 && (enemigo == BLANCA || enemigo == DAMA_BLANCA)) { fc = fEn; cc = cEn; return true; }
    }
    return false;
}

bool esMovimientoSimple(int f1, int c1, int f2, int c2, int jugador) {
    if (!posicionValida(f2, c2)) return false;
    if (tablero[f2][c2] != VACIO) return false;
    char pieza = tablero[f1][c1];
    int df = f2 - f1;
    int dc = c2 - c1;
    if (esDama(pieza)) {
        if (abs(df) != abs(dc)) return false;
        int dirF = (df > 0) ? 1 : -1;
        int dirC = (dc > 0) ? 1 : -1;
        int pasos = abs(df);
        for (int k = 1; k < pasos; k++) {
            int rr = f1 + k * dirF;
            int ccpos = c1 + k * dirC;
            if (tablero[rr][ccpos] != VACIO) return false;
        }
        return true;
    } else {
        if (abs(df) != 1 || abs(dc) != 1) return false;
        if (jugador == 1) {
            if (df != -1) return false;
        } else {
            if (df != 1) return false;
        }
        return true;
    }
}

bool piezaTieneCaptura(int f, int c, int jugador) {
    char pieza = tablero[f][c];
    int fc, cc;
    if (esDama(pieza)) {
        int dirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
        for (int d = 0; d < 4; d++) {
            int df = dirs[d][0], dc = dirs[d][1];
            int rr = f + df;
            int ccpos = c + dc;
            while (posicionValida(rr, ccpos)) {
                if (esCapturaDama(f, c, rr, ccpos, jugador, fc, cc)) return true;
                rr += df; ccpos += dc;
            }
        }
        return false;
    } else {
        int saltos[4][2] = {{2,2},{2,-2},{-2,2},{-2,-2}};
        for (int s = 0; s < 4; s++) {
            int rr = f + saltos[s][0];
            int ccpos = c + saltos[s][1];
            if (esCapturaMano(f, c, rr, ccpos, jugador, fc, cc)) return true;
        }
        return false;
    }
}

bool hayCapturaDisponible(int jugador) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            if (esPiezaJugador(jugador, tablero[i][j])) {
                if (piezaTieneCaptura(i,j,jugador)) return true;
            }
        }
    }
    return false;
}

bool realizarMovimiento(int f1, int c1, int f2, int c2, int jugador) {
    int fc = -1, cc = -1;
    bool esCap = false;
    char pieza = tablero[f1][c1];
    if (esDama(pieza)) {
        if (esCapturaDama(f1,c1,f2,c2,jugador,fc,cc)) esCap = true;
    } else {
        if (esCapturaMano(f1,c1,f2,c2,jugador,fc,cc)) esCap = true;
    }

    if (esCap) {
        tablero[f2][c2] = tablero[f1][c1];
        tablero[f1][c1] = VACIO;
        tablero[fc][cc] = VACIO;
        if (tablero[f2][c2] == BLANCA && f2 == 0) tablero[f2][c2] = DAMA_BLANCA;
        if (tablero[f2][c2] == NEGRA && f2 == TAMANO-1) tablero[f2][c2] = DAMA_NEGRA;
        mostrarTablero();
        std::cout << C_VERDE << "Captura realizada" << RESET << std::endl;
        if (piezaTieneCaptura(f2,c2,jugador)) {
            std::cout << C_AZUL << "Puedes seguir capturando con la misma pieza (movimiento encadenado)." << RESET << std::endl;
            return false;
        } else {
            return true;
        }
    } else {
        if (!esMovimientoSimple(f1,c1,f2,c2,jugador)) {
            std::cout << C_ROJO << "Movimiento inválido" << RESET << std::endl;
            return false;
        }
        tablero[f2][c2] = tablero[f1][c1];
        tablero[f1][c1] = VACIO;
        if (tablero[f2][c2] == BLANCA && f2 == 0) tablero[f2][c2] = DAMA_BLANCA;
        if (tablero[f2][c2] == NEGRA && f2 == TAMANO-1) tablero[f2][c2] = DAMA_NEGRA;
        return true;
    }
}

bool jugadorTieneMovimientos(int jugador) {
    for (int i = 0; i < TAMANO; i++) {
        for (int j = 0; j < TAMANO; j++) {
            if (!esPiezaJugador(jugador, tablero[i][j])) continue;
            char pieza = tablero[i][j];
            if (piezaTieneCaptura(i,j,jugador)) return true;
            if (esDama(pieza)) {
                int dirs[4][2] = {{1,1},{1,-1},{-1,1},{-1,-1}};
                for (int d = 0; d < 4; d++) {
                    int df = dirs[d][0], dc = dirs[d][1];
                    int rr = i + df, cc = j + dc;
                    while (posicionValida(rr,cc)) {
                        if (tablero[rr][cc] == VACIO) return true;
                        else break;
                    }
                }
            } else {
                for (int dc = -1; dc <= 1; dc += 2) {
                    int rr = (jugador==1)? i-1 : i+1;
                    int cc = j + dc;
                    if (posicionValida(rr,cc) && tablero[rr][cc] == VACIO) return true;
                }
            }
        }
    }
    return false;
}

int contarPiezas(int jugador) {
    int cont = 0;
    for (int i = 0; i < TAMANO; i++)
        for (int j = 0; j < TAMANO; j++)
            if (esPiezaJugador(jugador, tablero[i][j])) cont++;
    return cont;
}

bool verificarVictoriaYMostrar(int jugadorActual, const std::string &nombreJugador1, const std::string &nombreJugador2) {
    int otro = (jugadorActual == 1) ? 2 : 1;
    if (contarPiezas(otro) == 0) {
        std::cout << C_VERDE << std::endl << "Victoria! " << (jugadorActual==1?nombreJugador1:nombreJugador2)
                  << " ha capturado todas las piezas del oponente." << RESET << std::endl;
        return true;
    }
    if (!jugadorTieneMovimientos(otro)) {
        std::cout << C_VERDE << std::endl << "Victoria! " << (jugadorActual==1?nombreJugador1:nombreJugador2)
                  << " ha dejado al oponente sin movimientos válidos." << RESET << std::endl;
        return true;
    }
    return false;
}
