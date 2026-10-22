#include "partida.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "humano.h"
#include "ia_aleatoria.h"
#include "ia_estrategica.h"
#include "ia_super.h"

Partida::Partida() {
    jugador1 = nullptr;
    jugador2 = nullptr;
}

Partida::~Partida() {
    liberar_memoria();
}

void Partida::inicializar(const std::string& nombreJugador, int tipoIA) {
    liberar_memoria(); // Limpiamos la memoria de la partida anterior si existía

    // 1. Instanciamos al humano
    jugador1 = new Humano();

    // 2. Instanciamos la IA según la opción elegida en el ComboBox
    switch (tipoIA) {
    case 0:
        jugador2 = new IA_aleatoria();
        break;
    case 1:
        jugador2 = new IA_estrategica();
        break;
    case 2:
        jugador2 = new IA_super();
        break;
    default:
        jugador2 = new IA_aleatoria();
        break;
    }

    this->tipoIA = tipoIA; // Guardar el tipo de IA para poder exportarlo al guardar

    repartir_cartas(jugador1);
    repartir_cartas(jugador2);
}

// Lógica de combate turno a turno
void Partida::jugarTurno(int indiceHumano) {
    if (!jugador1 || !jugador2) return;

    Elemento* cartaJ1 = jugador1->obtener_elemento(indiceHumano);
    if (!cartaJ1 || !cartaJ1->estaVivo()) return;

    Elemento* cartaJ2 = nullptr;

    // Intentamos hacer un cast dinámico para verificar si es la Super IA
    IA_super* superIA = dynamic_cast<IA_super*>(jugador2);
    if (superIA) {
        cartaJ2 = superIA->seleccionar_elemento(cartaJ1, adminDanio);
    } else {
        cartaJ2 = jugador2->seleccionar_elemento();
    }

    if (cartaJ2 && cartaJ2->estaVivo()) {
        int danioJ1 = adminDanio.obtener_danio(static_cast<int>(cartaJ1->obtener_tipo()), static_cast<int>(cartaJ2->obtener_tipo()));
        int danioJ2 = adminDanio.obtener_danio(static_cast<int>(cartaJ2->obtener_tipo()), static_cast<int>(cartaJ1->obtener_tipo()));

        cartaJ2->recibirDanio(danioJ1);
        cartaJ1->recibirDanio(danioJ2);
    }
}

// Verifica si alguno de los dos se quedó sin cartas con vida
bool Partida::esFinDeJuego() const {
    if (!jugador1 || !jugador2) return false;

    bool j1TieneVida = false;
    bool j2TieneVida = false;

    for (int i = 0; i < 5; i++) {
        Elemento* e1 = jugador1->obtener_elemento(i);
        Elemento* e2 = jugador2->obtener_elemento(i);

        if (e1 && e1->estaVivo()) j1TieneVida = true;
        if (e2 && e2->estaVivo()) j2TieneVida = true;
    }

    return (!j1TieneVida || !j2TieneVida);
}

// Retorna el resultado para mostrar en la pantalla final (Página 3)
std::string Partida::obtenerResultadoFinal() const {
    if (!jugador1 || !jugador2) return "Partida no iniciada";

    bool j1TieneVida = false;
    bool j2TieneVida = false;

    std::string resumen = "";

    for (int i = 0; i < 5; i++) {
        Elemento* e1 = jugador1->obtener_elemento(i);
        Elemento* e2 = jugador2->obtener_elemento(i);

        if (e1 && e1->estaVivo()) j1TieneVida = true;
        if (e2 && e2->estaVivo()) j2TieneVida = true;
    }

    if (!j1TieneVida && !j2TieneVida) {
        resumen = "¡Empate técnico!\n\n";
    } else if (j1TieneVida) {
        resumen = "¡Felicidades, ganaste la partida!\n\n";
    } else {
        resumen = "¡La IA ha ganado la batalla!\n\n";
    }

    resumen += "--- Energías Finales ---\n";
    resumen += "Tus elementos:\n";
    for (int i = 0; i < 5; i++) {
        Elemento* e1 = jugador1->obtener_elemento(i);
        if (e1) {
            resumen += " - Elemento " + std::to_string(i+1) + ": " +
                       (e1->estaVivo() ? std::to_string(e1->obtener_vida()) + "%" : "Derrotado") + "\n";
        }
    }

    return resumen;
}

bool Partida::guardarPartida(const std::string& archivo) {
    if (!jugador1 || !jugador2) return false;

    std::ofstream out(archivo); // Usa la ruta/nombre que le pases por parámetro
    if (!out.is_open()) return false;

    out << tipoIA << "\n";

    for (int i = 0; i < 5; i++) {
        Elemento* elem = jugador1->obtener_elemento(i);
        out << (elem ? elem->obtener_vida() : 0) << "\n";
    }

    for (int i = 0; i < 5; i++) {
        Elemento* elem = jugador2->obtener_elemento(i);
        out << (elem ? elem->obtener_vida() : 0) << "\n";
    }

    out.close();
    return true;
}

bool Partida::cargarPartida(const std::string& archivo) {
    std::ifstream in(archivo);
    if (!in.is_open()) return false;

    int tipoIAGuardado = 0;
    if (!(in >> tipoIAGuardado)) {
        in.close();
        return false;
    }

    // Re-inicializa la partida con la IA guardada (crea las cartas al 100% de vida)
    inicializar("Jugador", tipoIAGuardado);

    // 1. Restaurar las vidas del Jugador 1
    for (int i = 0; i < 5; i++) {
        int vidaGuardada;
        if (in >> vidaGuardada) {
            Elemento* elem = jugador1->obtener_elemento(i);
            if (elem) {
                int danioAAplicar = 100 - vidaGuardada;
                if (danioAAplicar > 0) {
                    elem->recibirDanio(danioAAplicar);
                }
            }
        }
    }

    // 2. Restaurar las vidas de la IA (Jugador 2)
    for (int i = 0; i < 5; i++) {
        int vidaGuardada;
        if (in >> vidaGuardada) {
            Elemento* elem = jugador2->obtener_elemento(i);
            if (elem) {
                int danioAAplicar = 100 - vidaGuardada;
                if (danioAAplicar > 0) {
                    elem->recibirDanio(danioAAplicar);
                }
            }
        }
    }

    in.close();
    return true;
}

// Asignación aleatoria de elementos (incluye AIRE = % 4)
void Partida::repartir_cartas(Jugador* jugador) {
    if (!jugador) return;

    for (int i = 0; i < 5; i++) {
        // Asigna un tipo aleatorio entre 0 y 3 (Agua, Tierra, Fuego, Aire)
        TipoElemento tipoAleatorio = static_cast<TipoElemento>(rand() % 4);

        // Instancia la carta con 100 de energía inicial
        jugador->asignar_carta(i, new Elemento(100, tipoAleatorio));
    }
}

void Partida::liberar_memoria() {
    delete jugador1;
    delete jugador2;
    jugador1 = nullptr;
    jugador2 = nullptr;
}

Jugador* Partida::getJugador1() {
    return jugador1;
}

Jugador* Partida::getJugador2() {
    return jugador2;
}