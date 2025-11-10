#include "juego.h"
#include "movimiento.h"
#include "utilidades.h"
#include <iostream>

using namespace std;

char tableroJuego[TAMANO][TAMANO];
Jugador jugador1;
Jugador jugador2;
int jugadorActual = 1;
bool juegoActivo = true;

void configurarJugadores() {
    inicializarJugador(&jugador1, 1);
    inicializarJugador(&jugador2, 2);
    configurarJugador(&jugador1);
    configurarJugador(&jugador2);
}

int leerEntrada(const char* mensaje) {
    int valor;
    cout << mensaje;
    cin >> valor;
    
    if (valor == -1) {
        cout << "\nEstas seguro de que quieres salir? (1=Si, 0=No): ";
        int confirmar;
        cin >> confirmar;
        if (confirmar == 1) {
            juegoActivo = false;
            return -1;
        } else {
            cout << "Continuando el juego...\n";
            pausar();
            return leerEntrada(mensaje);
        }
    }
    
    if (valor == -2) {
        mostrarInstrucciones();
        return leerEntrada(mensaje);
    }
    
    return valor;
}

void iniciarJuego() {
    inicializarTablero(tableroJuego);
    configurarJugadores();
    jugadorActual = 1;
    juegoActivo = true;
    
    // Mostrar instrucciones al inicio
    mostrarInstrucciones();

    while (juegoActivo) {
        if (!ejecutarTurno()) {
            break;
        }
        
        if (verificarVictoria(tableroJuego)) {
            pausar();
            break;
        }
        
        jugadorActual = (jugadorActual == 1) ? 2 : 1;
    }
    
    if (!juegoActivo) {
        cout << "\nJuego terminado por el usuario!\n";
        pausar();
    }
}

bool ejecutarTurno() {
    if (!juegoActivo) return false;
    
    mostrarTablero(tableroJuego);
    
    Jugador* jugadorActivo = (jugadorActual == 1) ? &jugador1 : &jugador2;
    
    cout << "\n========================================\n";
    cout << "Turno de " << jugadorActivo->nombre
         << " (" << (jugadorActual == 1 ? "Blancas" : "Negras") << ")\n";
    cout << "========================================\n";
    cout << "Comandos: -1 (Salir) | -2 (Ayuda)\n";
    cout << "========================================\n";

    int f1 = leerEntrada("Fila origen: ");
    if (!juegoActivo) return false;
    
    int c1 = leerEntrada("Columna origen: ");
    if (!juegoActivo) return false;
    
    int f2 = leerEntrada("Fila destino: ");
    if (!juegoActivo) return false;
    
    int c2 = leerEntrada("Columna destino: ");
    if (!juegoActivo) return false;

    if (!esPosicionValida(f1, c1) || !esPosicionValida(f2, c2)) {
        cout << "\nMovimiento fuera de rango.\n";
        pausar();
        return true;
    }

    char pieza = obtenerPieza(tableroJuego, f1, c1);
    
    if (!esSuPieza(jugadorActivo, pieza)) {
        cout << "\nEsa pieza no te pertenece.\n";
        pausar();
        return true;
    }

    int filaComida, colComida;
    if (esMovimientoSimpleValido(tableroJuego, f1, c1, f2, c2, jugadorActual) ||
        esCaptura(tableroJuego, f1, c1, f2, c2, jugadorActual, filaComida, colComida)) {
        realizarMovimiento(tableroJuego, f1, c1, f2, c2, jugadorActual);
        cout << "\nMovimiento realizado con exito!\n";
        pausar();
    } else {
        cout << "\nMovimiento invalido.\n";
        pausar();
        return true;
    }
    
    return true;
}

void mostrarMenu() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "\n========================================\n";
        cout << "            JUEGO DE DAMAS              \n";
        cout << "========================================\n";
        cout << "1. Jugar\n";
        cout << "2. Ver Instrucciones\n";
        cout << "3. Salir\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        cin >> opcion;
        
        switch(opcion) {
            case 1:
                iniciarJuego();
                break;
            case 2:
                mostrarInstrucciones();
                break;
            case 3:
                cout << "\nGracias por jugar! :)\n";
                break;
            default:
                cout << "\nOpcion invalida. Intenta de nuevo.\n";
                pausar();
        }
    } while (opcion != 3);
}