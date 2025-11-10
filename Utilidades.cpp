#include "utilidades.h"
#include <iostream>
#include <cstdlib>
#include <limits>

using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    cout << "\nPresiona Enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void mostrarInstrucciones() {
    limpiarPantalla();
    cout << "\n========================================\n";
    cout << "         INSTRUCCIONES DEL JUEGO        \n";
    cout << "========================================\n\n";
    
    cout << "OBJETIVO:\n";
    cout << "  Capturar todas las piezas del oponente\n\n";
    
    cout << "PIEZAS:\n";
    cout << "  b = Pieza Blanca (Jugador 1)\n";
    cout << "  n = Pieza Negra (Jugador 2)\n";
    cout << "  B = Dama Blanca\n";
    cout << "  N = Dama Negra\n";
    cout << "  . = Casilla vacia\n\n";
    
    cout << "MOVIMIENTOS:\n";
    cout << "  - Las piezas se mueven en diagonal\n";
    cout << "  - Las piezas normales solo avanzan:\n";
    cout << "    * Blancas: hacia arriba (fila menor)\n";
    cout << "    * Negras: hacia abajo (fila mayor)\n";
    cout << "  - Las damas pueden moverse en cualquier direccion\n\n";
    
    cout << "CAPTURAS:\n";
    cout << "  - Salta sobre la pieza enemiga en diagonal\n";
    cout << "  - La pieza enemiga es eliminada\n";
    cout << "  - Puedes hacer capturas multiples seguidas\n\n";
    
    cout << "CORONACION:\n";
    cout << "  - Las blancas se coronan al llegar a la fila 0\n";
    cout << "  - Las negras se coronan al llegar a la fila 9\n";
    cout << "  - Una dama tiene mas libertad de movimiento\n\n";
    
    cout << "COMO JUGAR:\n";
    cout << "  1. Ingresa la fila de origen (0-9)\n";
    cout << "  2. Ingresa la columna de origen (0-9)\n";
    cout << "  3. Ingresa la fila de destino (0-9)\n";
    cout << "  4. Ingresa la columna de destino (0-9)\n\n";
    
    cout << "COMANDOS ESPECIALES:\n";
    cout << "  -1 : Salir del juego en cualquier momento\n";
    cout << "  -2 : Ver estas instrucciones nuevamente\n\n";
    
    cout << "========================================\n";
    pausar();
}