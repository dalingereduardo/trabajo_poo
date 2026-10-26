#include "ia_aleatoria.h"
#include <cstdlib>

// Constructor de la clase IA_aleatoria: inicializa la clase base IA
IA_aleatoria::IA_aleatoria(): IA() {}

// Destructor de la clase IA_aleatoria
IA_aleatoria::~IA_aleatoria() {}

// Método sobrescrito para que la IA elija un elemento de su mazo de forma aleatoria entre los que siguen vivos
Elemento* IA_aleatoria::seleccionar_elemento() {
    int indicesValidos[4]; // Arreglo auxiliar para almacenar temporalmente los índices de las cartas disponibles
    int cantidadValidas = 0; // Contador para llevar la cantidad de cartas válidas encontradas

    // Guardamos los índices de las cartas que existen y están vivas
    for (int i = 0; i < 5; i++) {
        // Verifica que la posición en el mazo no sea nula y que el elemento tenga vida mayor a 0
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            indicesValidos[cantidadValidas] = i; // Almacena el índice válido
            cantidadValidas++; // Incrementa el contador de cartas disponibles
        }
    }

    // Si no le quedan cartas vivas, retornamos nullptr
    if (cantidadValidas == 0) {
        return nullptr;
    }

    // Seleccionamos al azar solo entre las cartas que sabemos que están vivas
    int seleccion = rand() % cantidadValidas; // Genera un número aleatorio dentro del rango de cartas válidas
    return elementos[indicesValidos[seleccion]]; // Retorna el elemento elegido al azar
}