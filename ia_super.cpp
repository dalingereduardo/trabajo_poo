#include "ia_super.h"

// Constructor de la clase IA_super: inicializa la clase base IA
IA_super::IA_super() : IA() {}

// Destructor de la clase IA_super
IA_super::~IA_super() {}

// Método avanzado y principal de la Super IA: evalúa el elemento actual del oponente y la matriz de daño para tomar una decisión táctica óptima
Elemento* IA_super::seleccionar_elemento(Elemento* elementoHumano, AdministradorDanio& adminDanio) {
    // Valida que el elemento del oponente exista y siga con vida
    if (!elementoHumano || !elementoHumano->estaVivo()) {
        return seleccionar_elemento(); // Aplica el método de respaldo (fallback) si no hay un objetivo válido
    }

    // Convierte el tipo de elemento del humano a entero y obtiene su vida actual
    int tipoHumano = static_cast<int>(elementoHumano->obtener_tipo());
    int vidaHumano = elementoHumano->obtener_vida();

    // Variables para rastrear la mejor opción de remate (derrotar al rival en este turno)
    Elemento* mejorCartaRemate = nullptr;
    int menorDanioRecibidoRemate = 999;

    // Variables para rastrear la opción con mayor ventaja táctica general
    Elemento* mejorCartaVentaja = nullptr;
    int maxVentaja = -999;

    // Recorremos las 5 cartas del mazo de la IA
    for (int i = 0; i < 5; i++) {
        // Verifica que la carta exista en el mazo y que siga con vida
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            int tipoIA = static_cast<int>(elementos[i]->obtener_tipo());

            // Consulta la matriz de daño a través del administrador
            int danioAInfligir = adminDanio.obtener_danio(tipoIA, tipoHumano); // Daño que la IA inflige al humano
            int danioARecibir  = adminDanio.obtener_danio(tipoHumano, tipoIA); // Daño que la IA recibiría del humano
            int ventajaNeto    = danioAInfligir - danioARecibir;             // Balance de daño neto

            // 1. REGLA DE EFICIENCIA/REMATE: Si el ataque de la IA quita igual o más vida que la que le queda al humano
            if (danioAInfligir >= vidaHumano) {
                // Entre las cartas que pueden rematar, prefiere aquella que reciba menos daño a cambio
                if (danioARecibir < menorDanioRecibidoRemate) {
                    menorDanioRecibidoRemate = danioARecibir;
                    mejorCartaRemate = elementos[i];
                }
            }

            // 2. REGLA DE VENTAJA MÁXIMA: Busca maximizar el daño infligido y minimizar el recibido
            if (ventajaNeto > maxVentaja) {
                maxVentaja = ventajaNeto;
                mejorCartaVentaja = elementos[i];
            }
        }
    }

    // Prioridad 1: Si hay una carta capaz de eliminar al rival de forma eficiente, se utiliza inmediatamente
    if (mejorCartaRemate != nullptr) {
        return mejorCartaRemate;
    }

    // Prioridad 2: Si no es posible un remate directo, se utiliza la carta que ofrezca la mayor ventaja táctica neta
    if (mejorCartaVentaja != nullptr) {
        return mejorCartaVentaja;
    }

    // Respaldo final en caso de que ninguna regla anterior aplique
    return seleccionar_elemento();
}

// Método heredado sobrescrito (sobrecarga simple): retorna la primera carta viva disponible en el mazo de la IA
Elemento* IA_super::seleccionar_elemento() {
    // Recorre secuencialmente el mazo de 5 cartas
    for (int i = 0; i < 5; i++) {
        // Retorna el primer elemento que exista y tenga vida mayor a cero
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            return elementos[i];
        }
    }
    return nullptr; // Retorna nullptr si no quedan cartas vivas
}