#include "jugador.h"
#include <cstdlib>

// Constructor de la clase base Jugador: inicializa el mazo de 5 elementos asignando nullptr a cada posición
Jugador::Jugador() {
    for (int i = 0; i < 5; i++) {
        elementos[i] = nullptr;
    }
}

// Destructor de la clase base Jugador: recorre el mazo y libera la memoria dinámica de los elementos existentes para evitar fugas (memory leaks)
Jugador::~Jugador() {
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr) {
            delete elementos[i];     // Libera la memoria del elemento actual
            elementos[i] = nullptr;  // Establece el puntero en nulo por seguridad
        }
    }
}

// Método para contar y retornar cuántas cartas o elementos siguen con vida en el mazo del jugador
int Jugador::cantidad_cartas() {
    int cartas_vivas = 0; // Acumulador para las cartas operativas

    // Recorre los 5 elementos del mazo
    for (int i = 0; i < 5; i++) {
        // Verifica que la carta exista y que su vida sea mayor a cero
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            cartas_vivas++; // Incrementa el contador si la carta está viva
        }
    }

    return cartas_vivas; // Retorna el total de cartas con vida disponibles
}

// Método para asignar o reemplazar una carta en una posición específica del mazo del jugador
void Jugador::asignar_carta(int indice, Elemento* nueva_carta) {
    // Valida que el índice se encuentre dentro de los límites válidos del arreglo (0 a 4)
    if (indice >= 0 && indice < 5) {
        // Libera la memoria de la carta anterior si ya existía una en esa posición para evitar fugas de memoria
        if (elementos[indice] != nullptr) {
            delete elementos[indice];
        }
        elementos[indice] = nueva_carta; // Asigna el nuevo puntero de la carta a la posición indicada
    }
}