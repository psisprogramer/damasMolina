#include "juego.h"
#include "tablero.h"
#include "ficha.h"
#include <iostream>
#include <sstream>
#include <limits>
#include <string>
#include <windows.h>

std::string jugador1;
std::string jugador2;

int leerEnteroSeguro(std::string mensaje) {
    std::string linea;
    while (true) {
        std::cout << mensaje;
        if (!std::getline(std::cin, linea)) {
            std::cin.clear();
            continue;
        }
        std::stringstream ss(linea);
        int valor;
        if (ss >> valor) {
            std::string rest;
            if (!(ss >> rest)) return valor;
        }
        std::cout << "\a\n" ;
        std::cout << C_ROJO << "Entrada invalida. Introduce un numero entero." << RESET << std::endl;
        
    }
}

void pausarConEnter() {
    std::cout << std::endl << "Presiona Enter para continuar...";  
    Beep(1000, 150) ;
    std::string tmp;
    std::getline(std::cin, tmp);
}

void configurarJugadores() {
    std::cout << std::endl << "Nombre del Jugador 1 (Blancas, juega primero): ";
    std::getline(std::cin, jugador1);
    if (jugador1.size() == 0) jugador1 = "Jugador1";
    std::cout << "Nombre del Jugador 2 (Negras): ";
    std::getline(std::cin, jugador2);
    if (jugador2.size() == 0) jugador2 = "Jugador2";
}

void mostrarReglas() {
    limpiarPantalla();
    Beep(1000, 150) ;
    std::cout << std::endl << "==== REGLAS ====" << std::endl;
    std::cout << "- Tablero 10x10, se juega en casillas oscuras." << std::endl;
    std::cout << "- Blancas (b) comienzan en filas abajo; negras (n) arriba." << std::endl;
    std::cout << "- Movimiento simple: diagonal 1 casilla hacia adelante (piezas normales)." << std::endl;
    std::cout << "- Captura: salto sobre pieza enemiga a casilla vacia detras (obligatorio si existe)." << std::endl;
    std::cout << "- Capturas multiples permitidas en un mismo turno." << std::endl;
    std::cout << "- Dama: al coronar puede moverse y capturar a cualquier distancia diagonal." << std::endl;
    std::cout << "- Gana quien capture todas las piezas enemigas o deje al oponente sin movimientos." << std::endl << std::endl;
    pausarConEnter();
}

void jugarPartida() {
    inicializarTablero();
    configurarJugadores();
    int turno = 1;
    while (true) {
        mostrarTablero();
        std::cout << ((turno==1)?C_AZUL:C_ROJO)
                  << std::endl << "Turno de: " << (turno==1?jugador1:jugador2)
                  << " (" << (turno==1?"o Blancas":"x Negras") << ")" << RESET << std::endl;
        if (!jugadorTieneMovimientos(turno)) {
            std::cout << C_ROJO << "No tienes movimientos disponibles. Pierdes." << RESET << std::endl;
            break;
        }
        bool capturaObligatoria = hayCapturaDisponible(turno);
        if (capturaObligatoria) std::cout << C_AMAR << "Hay captura obligatoria! Debes capturar si es posible." << RESET << std::endl;
        int f1 = leerEnteroSeguro("Fila origen: ");
        int c1 = leerEnteroSeguro("Columna origen: ");
        if (!posicionValida(f1,c1)) { std::cout << C_ROJO << "Posicion de origen fuera de tablero." << RESET << std::endl; pausarConEnter(); continue; }
        char pieza = tablero[f1][c1];
        if (!esPiezaJugador(turno, pieza)) { std::cout << C_ROJO << "No hay una pieza tuya en esa casilla." << RESET << std::endl; pausarConEnter(); continue; }
        int f2 = leerEnteroSeguro("Fila destino: ");
        int c2 = leerEnteroSeguro("Columna destino: ");
        if (!posicionValida(f2,c2)) { std::cout << C_ROJO << "Posicion de destino fuera de tablero." << RESET << std::endl; pausarConEnter(); continue; }
        int fc=-1, cc=-1;
        bool movimientoEsCaptura = false;
        if (esDama(pieza)) movimientoEsCaptura = esCapturaDama(f1,c1,f2,c2,turno,fc,cc);
        else movimientoEsCaptura = esCapturaMano(f1,c1,f2,c2,turno,fc,cc);
        if (capturaObligatoria && !movimientoEsCaptura) {
            std::cout << C_ROJO << "Debes realizar una captura cuando exista una oportunidad." << RESET << std::endl;
            pausarConEnter();
            continue;
        }
        bool cambioTurno = realizarMovimiento(f1,c1,f2,c2,turno);
        if (tablero[f1][c1] != VACIO) {
            std::cout << C_ROJO << "Movimiento no realizado." << RESET << std::endl;
            pausarConEnter();
            continue;
        }
        if (verificarVictoriaYMostrar(turno, jugador1, jugador2)) { pausarConEnter(); break; }
        if (cambioTurno) turno = (turno==1)?2:1;
    }
    std::cout << std::endl << "Partida finalizada. Presiona Enter para volver al menu." << std::endl;
    pausarConEnter();
}

void mostrarMenu() {
    while (true) {
        limpiarPantalla();
         Beep(1000, 150) ;
        std::cout << C_AZUL << std::endl << "======== DAMAS INTERNACIONALES - EL RETO ========" << RESET << std::endl << std::endl;
        std::cout << "||" << "1. Lanzarse a la aventura (Nueva partida)!     "<< "||"<< std::endl;
        std::cout << "||" << "2. Sabiduria Ancestral (Ver reglas)            "<< "||"<< std::endl;
        std::cout << "||" << "3. ¡Rendicion! (Salir del juego)               "<< "||"<< std::endl;
        std::cout << C_AZUL << std::endl << "================================================="<< RESET << std::endl;
        int opcion = leerEnteroSeguro("  ---> Elige tu destino (1, 2 o 3): ");
        if (opcion == 1) {
            std::cout << std::endl << C_MORADO_REAL << BG_GRIS_PLATA << "Prepara tus fichas! La batalla está a punto de comenzar..." << std::endl;
           Beep(300, 400);
            pausarConEnter();
            jugarPartida();
            std::cout << "\a\n" ;
        } else if (opcion == 2) {
            std::cout << C_VERDE_LIMON << "\nDesempolvando el pergamino de la sabiduría milenaria..." << std::endl;
            mostrarReglas();
        } else if (opcion == 3) {
            std::cout << C_VERDE << std::endl << "\nAdios, gran estratega. Que los dados te sean favorables hasta que volvamos a vernos!" << RESET << std::endl;
            break;
        } else {
            std::cout << C_ROJO << "\n ERROR CRITICO DE ELECCION! Esa opcion no existe en este universo. Intenta de nuevo..." << RESET << std::endl;
            pausarConEnter();
        }
    }
}
