#include "ia_estrategica.h"
#include <cstdlib>

// Constructor de la clase IA_estrategica: inicializa la clase base IA
IA_estrategica::IA_estrategica(): IA() {}

// Destructor de la clase IA_estrategica
IA_estrategica::~IA_estrategica() {}

// Método sobrescrito para que la IA estratégica seleccione el elemento con mayor cantidad de vida disponible en su mazo
Elemento* IA_estrategica::seleccionar_elemento() {
    Elemento* mejor_carta = nullptr; // Puntero para almacenar temporalmente la mejor carta encontrada
    int max_vida = -1; // Variable para rastrear la vida máxima y comparar (inicializada en un valor menor a cero)

    // Iteramos sobre los 5 elementos del mazo (índices de 0 a 4)
    for (int i = 0; i < 5; i++) {
        // Verifica que la posición no sea nula y que el elemento siga con vida
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            // Comprueba si la vida del elemento actual es mayor al récord registrado hasta el momento
            if (elementos[i]->obtener_vida() > max_vida) {
                max_vida = elementos[i]->obtener_vida(); // Actualiza el valor de la vida máxima encontrada
                mejor_carta = elementos[i]; // Guarda la referencia al elemento con mayor vida
            }
        }
    }

    return mejor_carta; // Retorna la mejor carta viva encontrada o nullptr si perdió todas
}