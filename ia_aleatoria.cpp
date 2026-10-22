#include "ia_aleatoria.h"
#include <cstdlib>

IA_aleatoria::IA_aleatoria(): IA() {}

IA_aleatoria::~IA_aleatoria() {}

Elemento* IA_aleatoria::seleccionar_elemento() {
    int indicesValidos[4];
    int cantidadValidas = 0;

    // Guardamos los índices de las cartas que existen y están vivas
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            indicesValidos[cantidadValidas] = i;
            cantidadValidas++;
        }
    }

    // Si no le quedan cartas vivas, retornamos nullptr
    if (cantidadValidas == 0) {
        return nullptr;
    }

    // Seleccionamos al azar solo entre las cartas que sabemos que están vivas
    int seleccion = rand() % cantidadValidas;
    return elementos[indicesValidos[seleccion]];
}














