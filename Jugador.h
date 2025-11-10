#ifndef JUGADOR_HPP
#define JUGADOR_HPP

#include <string>

// Estructura para representar un jugador
struct Jugador {
    std::string nombre;
    int numero;
    char piezaTipo;
    char damaTipo;
};

// Funciones de jugador
void inicializarJugador(Jugador* jugador, int num);
void configurarJugador(Jugador* jugador);
bool esSuPieza(Jugador* jugador, char pieza);

#endif // JUGADOR_HPP