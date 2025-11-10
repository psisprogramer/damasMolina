#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <limits>
#include <cstdlib>

#define RESET   "\033[0m"
#define BG_DARK "\033[100m"
#define BG_LIGHT "\033[47m"
#define C_AZUL  "\033[36m"
#define C_ROJO  "\033[31m"
#define C_VERDE "\033[32m"
#define C_AMAR  "\033[33m"

int TAMANO = 10;
char VACIO = '.';
char BLANCA = 'b';
char NEGRA = 'n';
char DAMA_BLANCA = 'B';
char DAMA_NEGRA = 'N';

char tablero[20][20];
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
        std::cout << C_ROJO << "Entrada inválida. Introduce un número entero.\n" << RESET;
    }
}

void limpiarPantalla() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pausarConEnter() {
    std::cout << "\nPresiona Enter para continuar...";
    std::string tmp;
    std::getline(std::cin, tmp);
}

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
    limpiarPantalla();
    std::cout << "\n   " << C_AMAR;
    for (int j = 0; j < TAMANO; j++) {
        std::cout << " " << j << " ";
    }
    std::cout << RESET << "\n";
    for (int i = 0; i < TAMANO; i++) {
        std::cout << C_AMAR << " " << i << " " << RESET;
        for (int j = 0; j < TAMANO; j++) {
            bool oscuro = ((i + j) % 2 == 1);
            std::string fondo = oscuro ? BG_DARK : BG_LIGHT;
            std::cout << fondo << " " << simboloDe(tablero[i][j]) << " " << RESET;
        }
        std::cout << "\n";
    }
    std::cout << "\nLeyenda: b=blanca  n=negra  B=dama blanca  N=dama negra\n";
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
    if (std::abs(df) != 2 || std::abs(dc) != 2) return false;
    int fm = f1 + df/2;
    int cm = c1 + dc/2;
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
    if (std::abs(df) != std::abs(dc)) return false;
    int dirF = (df > 0) ? 1 : -1;
    int dirC = (dc > 0) ? 1 : -1;
    int enemigos = 0;
    int fEn = -1, cEn = -1;
    int pasos = std::abs(df);
    for (int k = 1; k < pasos; k++) {
        int rr = f1 + k*dirF;
        int ccpos = c1 + k*dirC;
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
        if (std::abs(df) != std::abs(dc)) return false;
        int dirF = (df > 0) ? 1 : -1;
        int dirC = (dc > 0) ? 1 : -1;
        int pasos = std::abs(df);
        for (int k = 1; k < pasos; k++) {
            int rr = f1 + k*dirF;
            int ccpos = c1 + k*dirC;
            if (tablero[rr][ccpos] != VACIO) return false;
        }
        return true;
    } else {
        if (std::abs(df) != 1 || std::abs(dc) != 1) return false;
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
        std::cout << C_VERDE << "Captura realizada\n" << RESET;
        if (piezaTieneCaptura(f2,c2,jugador)) {
            std::cout << C_AZUL << "Puedes seguir capturando con la misma pieza (movimiento encadenado).\n" << RESET;
            return false;
        } else {
            return true;
        }
    } else {
        if (!esMovimientoSimple(f1,c1,f2,c2,jugador)) {
            std::cout << C_ROJO << "Movimiento inválido\n" << RESET;
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

bool verificarVictoriaYMostrar(int jugadorActual) {
    int otro = (jugadorActual == 1) ? 2 : 1;
    if (contarPiezas(otro) == 0) {
        std::cout << C_VERDE << "\nVictoria! " << (jugadorActual==1?jugador1:jugador2)
                  << " ha capturado todas las piezas del oponente.\n" << RESET;
        return true;
    }
    if (!jugadorTieneMovimientos(otro)) {
        std::cout << C_VERDE << "\nVictoria! " << (jugadorActual==1?jugador1:jugador2)
                  << " ha dejado al oponente sin movimientos válidos.\n" << RESET;
        return true;
    }
    return false;
}

void mostrarReglas() {
    limpiarPantalla();
    std::cout << "\n==== REGLAS ====\n";
    std::cout << "- Tablero 10x10, se juega en casillas oscuras.\n";
    std::cout << "- Blancas (b) comienzan en filas abajo; negras (n) arriba.\n";
    std::cout << "- Movimiento simple: diagonal 1 casilla hacia adelante (piezas normales).\n";
    std::cout << "- Captura: salto sobre pieza enemiga a casilla vacía detrás (obligatorio si existe).\n";
    std::cout << "- Capturas múltiples permitidas en un mismo turno.\n";
    std::cout << "- Dama: al coronar puede moverse y capturar a cualquier distancia diagonal.\n";
    std::cout << "- Gana quien capture todas las piezas enemigas o deje al oponente sin movimientos.\n\n";
    pausarConEnter();
}

void configurarJugadores() {
    std::cout << "\nNombre del Jugador 1 (Blancas, juega primero): ";
    std::getline(std::cin, jugador1);
    if (jugador1.size() == 0) jugador1 = "Jugador1";
    std::cout << "Nombre del Jugador 2 (Negras): ";
    std::getline(std::cin, jugador2);
    if (jugador2.size() == 0) jugador2 = "Jugador2";
}

void jugarPartida() {
    inicializarTablero();
    configurarJugadores();
    int turno = 1;
    while (true) {
        mostrarTablero();
        std::cout << ((turno==1)?C_AZUL:C_ROJO)
                  << "\nTurno de: " << (turno==1?jugador1:jugador2)
                  << " (" << (turno==1?"b Blancas":"n Negras") << ")\n" << RESET;
        if (!jugadorTieneMovimientos(turno)) {
            std::cout << C_ROJO << "No tienes movimientos disponibles. Pierdes.\n" << RESET;
            break;
        }
        bool capturaObligatoria = hayCapturaDisponible(turno);
        if (capturaObligatoria) std::cout << C_AMAR << "Hay captura obligatoria! Debes capturar si es posible.\n" << RESET;
        int f1 = leerEnteroSeguro("Fila origen: ");
        int c1 = leerEnteroSeguro("Columna origen: ");
        if (!posicionValida(f1,c1)) { std::cout << C_ROJO << "Posición de origen fuera de tablero.\n" << RESET; pausarConEnter(); continue; }
        char pieza = tablero[f1][c1];
        if (!esPiezaJugador(turno, pieza)) { std::cout << C_ROJO << "No hay una pieza tuya en esa casilla.\n" << RESET; pausarConEnter(); continue; }
        int f2 = leerEnteroSeguro("Fila destino: ");
        int c2 = leerEnteroSeguro("Columna destino: ");
        if (!posicionValida(f2,c2)) { std::cout << C_ROJO << "Posición de destino fuera de tablero.\n" << RESET; pausarConEnter(); continue; }
        int fc=-1, cc=-1;
        bool movimientoEsCaptura = false;
        if (esDama(pieza)) movimientoEsCaptura = esCapturaDama(f1,c1,f2,c2,turno,fc,cc);
        else movimientoEsCaptura = esCapturaMano(f1,c1,f2,c2,turno,fc,cc);
        if (capturaObligatoria && !movimientoEsCaptura) {
            std::cout << C_ROJO << "Debes realizar una captura cuando exista una oportunidad.\n" << RESET;
            pausarConEnter();
            continue;
        }
        bool cambioTurno = realizarMovimiento(f1,c1,f2,c2,turno);
        if (tablero[f1][c1] != VACIO) {
            std::cout << C_ROJO << "Movimiento no realizado.\n" << RESET;
            pausarConEnter();
            continue;
        }
        if (verificarVictoriaYMostrar(turno)) { pausarConEnter(); break; }
        if (cambioTurno) turno = (turno==1)?2:1;
    }
    std::cout << "\nPartida finalizada. Presiona Enter para volver al menu.\n";
    pausarConEnter();
}

void mostrarMenu() {
    while (true) {
        limpiarPantalla();
        std::cout << C_AZUL << "\n===== DAMAS INTERNACIONALES (BASICO) =====\n" << RESET;
        std::cout << "1. Iniciar nueva partida\n2. Ver reglas\n3. Salir\n";
        int opcion = leerEnteroSeguro("Selecciona una opción: ");
        if (opcion == 1) {
            std::cout << "\nIniciando partida...\n";
            pausarConEnter();
            jugarPartida();
        } else if (opcion == 2) {
            mostrarReglas();
        } else if (opcion == 3) {
            std::cout << C_VERDE << "\nGracias por jugar. ¡Hasta la proxima!\n" << RESET;
            break;
        } else {
            std::cout << C_ROJO << "Opcion inválida.\n" << RESET;
            pausarConEnter();
        }
    }
}

int main() {
    mostrarMenu();
    return 0;
}
