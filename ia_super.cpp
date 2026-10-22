#include "ia_super.h"

IA_super::IA_super() : IA() {}

IA_super::~IA_super() {}

Elemento* IA_super::seleccionar_elemento(Elemento* elementoHumano, AdministradorDanio& adminDanio) {
    if (!elementoHumano || !elementoHumano->estaVivo()) {
        return seleccionar_elemento(); // Fallback si no hay objetivo válido
    }

    int tipoHumano = static_cast<int>(elementoHumano->obtener_tipo());
    int vidaHumano = elementoHumano->obtener_vida();

    Elemento* mejorCartaRemate = nullptr;
    int menorDanioRecibidoRemate = 999;

    Elemento* mejorCartaVentaja = nullptr;
    int maxVentaja = -999;

    // Recorremos las 5 cartas de la IA
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            int tipoIA = static_cast<int>(elementos[i]->obtener_tipo());

            int danioAInfligir = adminDanio.obtener_danio(tipoIA, tipoHumano);
            int danioARecibir  = adminDanio.obtener_danio(tipoHumano, tipoIA);
            int ventajaNeto   = danioAInfligir - danioARecibir;

            // 1. REGLA DE EFICIENCIA/REMATE: Si el ataque quita igual o más que la vida restante del humano
            if (danioAInfligir >= vidaHumano) {
                // Entre las que pueden rematar, prefiere la que reciba menos daño a cambio
                if (danioARecibir < menorDanioRecibidoRemate) {
                    menorDanioRecibidoRemate = danioARecibir;
                    mejorCartaRemate = elementos[i];
                }
            }

            // 2. REGLA DE VENTAJA MÁXIMA: Maximiza el daño infligido y minimiza el recibido
            if (ventajaNeto > maxVentaja) {
                maxVentaja = ventajaNeto;
                mejorCartaVentaja = elementos[i];
            }
        }
    }

    // Prioridad 1: Si hay una carta que remate de forma eficiente, la usa
    if (mejorCartaRemate != nullptr) {
        return mejorCartaRemate;
    }

    // Prioridad 2: Si no puede rematar, usa la que dé la mayor ventaja táctica
    if (mejorCartaVentaja != nullptr) {
        return mejorCartaVentaja;
    }

    return seleccionar_elemento();
}

Elemento* IA_super::seleccionar_elemento() {
    // Retorna la primera carta viva disponible
    for (int i = 0; i < 5; i++) {
        if (elementos[i] != nullptr && elementos[i]->estaVivo()) {
            return elementos[i];
        }
    }
    return nullptr;
}