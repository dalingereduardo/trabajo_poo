#include "jugador.h"
#include <cstdlib>

Jugador::Jugador() {
    for (int i = 0; i < 5; i++) {
        elementos[i] = nullptr;
    }
}

Jugador::~Jugador() {
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr) {
            delete elementos[i];
            elementos[i] = nullptr;
        }
    }
}

int Jugador::cantidad_cartas() {
    int cartas_vivas = 0;

    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            cartas_vivas++;
        }
    }

    return cartas_vivas;
}

void Jugador::asignar_carta(int indice, Elemento* nueva_carta) {
    if (indice >= 0 && indice < 5) {
        // Libera la memoria de la carta anterior si existía para evitar fugas
        if (elementos[indice] != nullptr) {
            delete elementos[indice];
        }
        elementos[indice] = nueva_carta;
    }
}