#ifndef TABLERO_H
#define TABLERO_H

#include <string>
#define RESET   "\033[0m"
#define BG_DARK "\033[48;5;212m"
#define BG_LIGHT "\033[48;5;225m"
#define C_AZUL  "\033[36m"
#define C_ROJO  "\033[31m"
#define C_VERDE "\033[32m"
#define C_AMAR  "\033[33m"

// --- VINOTINTO / ROJOS PROFUNDOS ---
#define C_VINOTINTO      "\033[38;5;88m"
#define BG_VINOTINTO     "\033[48;5;88m"
#define C_ROJO_SANGRE    "\033[38;5;160m"
#define BG_ROJO_SANGRE   "\033[48;5;160m"
#define C_BERMELLON      "\033[38;5;196m"
#define BG_BERMELLON     "\033[48;5;196m"

// --- MORADOS / PÚRPURA ---
#define C_MORADO_REAL    "\033[38;5;99m"
#define BG_MORADO_REAL   "\033[48;5;99m"
#define C_LILA_MAGIA     "\033[38;5;183m"
#define BG_LILA_MAGIA    "\033[48;5;183m"
#define C_FUCSIA         "\033[38;5;201m"
#define BG_FUCSIA        "\033[48;5;201m"

// --- AZULES / CIANES ---
#define C_AZUL_CLARO     "\033[38;5;117m"
#define BG_AZUL_CLARO    "\033[48;5;117m"
#define C_CIAN_ELECTRICO "\033[38;5;51m"
#define BG_CIAN_ELECTRICO "\033[48;5;51m"
#define C_AZUL_NOCHE     "\033[38;5;18m"
#define BG_AZUL_NOCHE    "\033[48;5;18m"

// --- OTROS COLORES DE FANTASÍA ---
#define C_VERDE_LIMON    "\033[38;5;154m"
#define BG_VERDE_LIMON   "\033[48;5;154m"
#define C_NARANJA_FUEGO  "\033[38;5;208m"
#define BG_NARANJA_FUEGO "\033[48;5;208m"
#define C_AMARILLO_ORO   "\033[38;5;220m"
#define BG_AMARILLO_ORO  "\033[48;5;220m"
#define C_GRIS_PLATA     "\033[38;5;250m"
#define BG_GRIS_PLATA    "\033[48;5;250m"

extern int TAMANO;
extern char VACIO;
extern char BLANCA;
extern char NEGRA;
extern char DAMA_BLANCA;
extern char DAMA_NEGRA;
extern char tablero[20][20];

void inicializarTablero();
void mostrarTablero();
std::string simboloDe(char pieza);
bool verificarVictoriaYMostrar(int jugadorActual, const std::string &nombreJugador1, const std::string &nombreJugador2);
void limpiarPantalla();

#endif
