#include "tablero.h"
#include "ficha.h"
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

            char pieza = tablero[i][j];
            std::string simbolo;

            if (pieza == 'b')
                simbolo = "o"; 
            else if (pieza == 'n')
                simbolo = "x";  
            else if (pieza == 'B')
                simbolo = "O";  
            else if (pieza == 'N')
                simbolo = "X";  
            else
                simbolo = " ";  

            std::cout << fondo << " " << simbolo << " " << RESET;
        }

        std::cout << std::endl;
    }
}


void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
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





