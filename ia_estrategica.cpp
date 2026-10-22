#include "ia_estrategica.h"
#include <cstdlib>

IA_estrategica::IA_estrategica(): IA() {}

IA_estrategica::~IA_estrategica() {}

Elemento* IA_estrategica::seleccionar_elemento() {
    Elemento* mejor_carta = nullptr;
    int max_vida = -1;

    // Iteramos sobre los 5 elementos de la partida (0 a 3)
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            if (elementos[i]->obtener_vida() > max_vida) {
                max_vida = elementos[i]->obtener_vida();
                mejor_carta = elementos[i];
            }
        }
    }

    return mejor_carta; // Retorna la mejor carta viva o nullptr si perdió todas
}