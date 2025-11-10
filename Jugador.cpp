#include "jugador.h"
#include "tablero.h"
#include <iostream>
#include <limits>

using namespace std;

void inicializarJugador(Jugador* jugador, int num) {
    jugador->numero = num;
    if (num == 1) {
        jugador->piezaTipo = BLANCA;
        jugador->damaTipo = DAMA_BLANCA;
    } else {
        jugador->piezaTipo = NEGRA;
        jugador->damaTipo = DAMA_NEGRA;
    }
}

void configurarJugador(Jugador* jugador) {
    cout << "\nNombre del Jugador " << jugador->numero 
         << " (" << (jugador->numero == 1 ? "Blancas" : "Negras") << "): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, jugador->nombre);
}

bool esSuPieza(Jugador* jugador, char pieza) {
    return pieza == jugador->piezaTipo || pieza == jugador->damaTipo;
}