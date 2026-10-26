#include "partida.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "humano.h"
#include "ia_aleatoria.h"
#include "ia_estrategica.h"
#include "ia_super.h"
#include <QFile>
#include <QTextStream>
#include <QString>

// Constructor de la clase Partida: inicializa los punteros de ambos jugadores como nulos
Partida::Partida() {
    jugador1 = nullptr;
    jugador2 = nullptr;
}

// Destructor de la clase Partida: libera los recursos dinámicos asociados a los jugadores mediante el método auxiliar
Partida::~Partida() {
    liberar_memoria();
}

// Método para inicializar o reiniciar la partida configurando al jugador humano y seleccionando el tipo de IA según la interfaz
void Partida::inicializar(const std::string& /*nombreJugador*/, int tipoIA) {
    liberar_memoria(); // Limpiamos la memoria de la partida anterior si existía para evitar fugas

    // 1. Instanciamos al jugador humano
    jugador1 = new Humano();

    // 2. Instanciamos el oponente controlado por la inteligencia artificial según la opción elegida en el ComboBox
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

    this->tipoIA = tipoIA; // Guarda el tipo de IA para poder exportarlo correctamente al guardar la partida

    repartir_cartas(jugador1); // Reparte el mazo inicial de 5 elementos al jugador humano
    repartir_cartas(jugador2); // Reparte el mazo inicial de 5 elementos a la inteligencia artificial
}

// Lógica central de combate turno a turno entre el elemento seleccionado por el humano y el oponente de la IA
std::string Partida::jugarTurno(int indiceHumano) {
    // Valida que ambos jugadores se encuentren debidamente inicializados
    if (!jugador1 || !jugador2) return "Error: Jugadores no inicializados.";

    // Obtiene la carta seleccionada por el humano a partir de su índice en el mazo
    Elemento* cartaJ1 = jugador1->obtener_elemento(indiceHumano);
    if (!cartaJ1 || !cartaJ1->estaVivo()) return "El elemento seleccionado ya no tiene vida.";

    Elemento* cartaJ2 = nullptr;

    // Intenta realizar un cast dinámico para verificar si el oponente utiliza la Super IA avanzada
    IA_super* superIA = dynamic_cast<IA_super*>(jugador2);
    if (superIA) {
        cartaJ2 = superIA->seleccionar_elemento(cartaJ1, adminDanio); // La Super IA recibe el contexto del oponente y la matriz de daño
    } else {
        cartaJ2 = jugador2->seleccionar_elemento(); // Las IA estándar seleccionan mediante su propia lógica
    }

    // Valida que el elemento seleccionado por la IA exista y siga con vida
    if (!cartaJ2 || !cartaJ2->estaVivo()) {
        return "El elemento oponente no está disponible.";
    }

    // Consulta en el administrador de daños el daño recíproco entre ambos elementos según sus tipos
    int danioJ1 = adminDanio.obtener_danio(static_cast<int>(cartaJ1->obtener_tipo()), static_cast<int>(cartaJ2->obtener_tipo()));
    int danioJ2 = adminDanio.obtener_danio(static_cast<int>(cartaJ2->obtener_tipo()), static_cast<int>(cartaJ1->obtener_tipo()));

    // Aplica de forma simultánea el daño correspondiente sobre los puntos de vida de cada carta en combate
    cartaJ2->recibirDanio(danioJ1);
    cartaJ1->recibirDanio(danioJ2);

    // --- CONSTRUCCIÓN DEL REPORTE PARA EL HISTORIAL ---
    std::string reporte = "Turno:\n";
    reporte += " Tu " + tipoToString(cartaJ1->obtener_tipo()) + " atacó al " + tipoToString(cartaJ2->obtener_tipo()) + " enemigo causando " + std::to_string(danioJ1) + " de daño.\n";
    reporte += " La IA contraatacó causando " + std::to_string(danioJ2) + " de daño a tu elemento.\n";

    // Verifica si alguno de los elementos en combate fue eliminado tras el intercambio de golpes
    if (!cartaJ2->estaVivo()) {
        reporte += " ¡El elemento enemigo fue eliminado!\n";
    }
    if (!cartaJ1->estaVivo()) {
        reporte += " ¡Tu elemento fue eliminado!\n";
    }

    return reporte; // Retorna el texto detallado del resultado del turno
}

// Verifica si alguno de los jugadores se quedó completamente sin cartas con vida (condición de derrota)
bool Partida::esFinDeJuego() const {
    if (!jugador1 || !jugador2) return false;

    bool j1TieneVida = false;
    bool j2TieneVida = false;

    // Recorre los mazos de ambos jugadores evaluando si al menos un elemento sigue con vida
    for (int i = 0; i < 5; i++) {
        Elemento* e1 = jugador1->obtener_elemento(i);
        Elemento* e2 = jugador2->obtener_elemento(i);

        if (e1 && e1->estaVivo()) j1TieneVida = true;
        if (e2 && e2->estaVivo()) j2TieneVida = true;
    }

    return (!j1TieneVida || !j2TieneVida); // Retorna true si algún bando perdió todos sus elementos
}

// Retorna un resumen detallado con el resultado final para mostrar en la pantalla correspondiente
std::string Partida::obtenerResultadoFinal() const {
    if (!jugador1 || !jugador2) return "Partida no iniciada";

    bool j1TieneVida = false;
    bool j2TieneVida = false;

    std::string resumen = "";

    // Analiza el estado vital de todas las cartas de ambos jugadores
    for (int i = 0; i < 5; i++) {
        Elemento* e1 = jugador1->obtener_elemento(i);
        Elemento* e2 = jugador2->obtener_elemento(i);

        if (e1 && e1->estaVivo()) j1TieneVida = true;
        if (e2 && e2->estaVivo()) j2TieneVida = true;
    }

    // Determina el ganador de la partida según las existencias vitales restantes
    if (!j1TieneVida && !j2TieneVida) {
        resumen = "¡Empate técnico!\n\n";
    } else if (j1TieneVida) {
        resumen = "¡Felicidades, ganaste la partida!\n\n";
    } else {
        resumen = "¡La IA ha ganado la batalla!\n\n";
    }

    // Agrega al reporte el desglose de las energías finales de cada elemento del jugador
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

// Guarda el estado actual de la partida en un archivo de texto externo utilizando herramientas de Qt para asegurar la compatibilidad de rutas
bool Partida::guardarPartida(const std::string& archivo) {
    if (!jugador1 || !jugador2) return false;

    QFile file(QString::fromStdString(archivo));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false; // Retorna falso si el archivo no pudo ser abierto para escritura
    }

    QTextStream out(&file);
    out << tipoIA << "\n"; // Escribe primero el tipo de IA configurado en la partida

    // Escribe los puntos de vida de cada carta del jugador humano
    for (int i = 0; i < 5; i++) {
        Elemento* elem = jugador1->obtener_elemento(i);
        out << (elem ? elem->obtener_vida() : 0) << "\n";
    }

    // Escribe los puntos de vida de cada carta de la IA
    for (int i = 0; i < 5; i++) {
        Elemento* elem = jugador2->obtener_elemento(i);
        out << (elem ? elem->obtener_vida() : 0) << "\n";
    }

    file.close(); // Cierra el archivo de forma segura
    return true;  // Retorna true indicando que el guardado fue exitoso
}

// Carga una partida previamente guardada desde un archivo externo y restaura el estado y las vidas de los elementos
bool Partida::cargarPartida(const std::string& archivo) {
    QFile file(QString::fromStdString(archivo));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false; // Retorna falso si el archivo no existe o no se puede leer
    }

    QTextStream in(&file);

    if (in.atEnd()) return false;
    int nuevoTipoIA;
    in >> nuevoTipoIA; // Lee el tipo de IA guardado

    // Reinicializa los jugadores configurando el tipo de IA recuperado del archivo
    liberar_memoria();
    jugador1 = new Humano();

    switch (nuevoTipoIA) {
    case 0: jugador2 = new IA_aleatoria(); break;
    case 1: jugador2 = new IA_estrategica(); break;
    case 2: jugador2 = new IA_super(); break;
    default: jugador2 = new IA_aleatoria(); break;
    }
    tipoIA = nuevoTipoIA;

    repartir_cartas(jugador1);
    repartir_cartas(jugador2);

    // Lee y restaura las vidas correspondientes al mazo del jugador 1
    for (int i = 0; i < 5; i++) {
        if (in.atEnd()) { file.close(); return false; }
        int vida;
        in >> vida;
        Elemento* elem = jugador1->obtener_elemento(i);
        if (elem) {
            int vidaActual = elem->obtener_vida();
            if (vidaActual > vida) {
                elem->recibirDanio(vidaActual - vida); // Aplica el daño necesario para igualar la vida guardada
            }
        }
    }

    // Lee y restaura las vidas correspondientes al mazo del jugador 2 (IA)
    for (int i = 0; i < 5; i++) {
        if (in.atEnd()) { file.close(); return false; }
        int vida;
        in >> vida;
        Elemento* elem = jugador2->obtener_elemento(i);
        if (elem) {
            int vidaActual = elem->obtener_vida();
            if (vidaActual > vida) {
                elem->recibirDanio(vidaActual - vida); // Aplica el daño necesario para igualar la vida guardada
            }
        }
    }

    file.close(); // Cierra el archivo tras finalizar la restauración
    return true;  // Retorna true indicando que la carga se completó con éxito
}

// Método auxiliar para repartir aleatoriamente un mazo de 5 cartas con 100 de energía inicial a un jugador
void Partida::repartir_cartas(Jugador* jugador) {
    if (!jugador) return;

    for (int i = 0; i < 5; i++) {
        // Asigna un tipo de elemento aleatorio entre 0 y 3 (Agua, Tierra, Fuego, etc.)
        TipoElemento tipoAleatorio = static_cast<TipoElemento>(rand() % 4);

        // Instancia la nueva carta con 100 puntos de vida iniciales y la asigna al mazo
        jugador->asignar_carta(i, new Elemento(100, tipoAleatorio));
    }
}

// Método privado para liberar de forma segura la memoria dinámica asignada a ambos jugadores
void Partida::liberar_memoria() {
    delete jugador1;
    delete jugador2;
    jugador1 = nullptr;
    jugador2 = nullptr;
}

// Método selector (getter) para obtener el puntero al jugador 1 (Humano)
Jugador* Partida::getJugador1() {
    return jugador1;
}

// Método selector (getter) para obtener el puntero al jugador 2 (IA)
Jugador* Partida::getJugador2() {
    return jugador2;
}

// Comprueba si el juego ha terminado y asigna el mensaje correspondiente del ganador por referencia
bool Partida::juegoTerminado(std::string& mensajeGanador) {
    if (!jugador1 || !jugador2) return false;

    bool p1Vivo = false;
    for (int i = 0; i < 5; i++) {
        Elemento* e = jugador1->obtener_elemento(i);
        if (e && e->estaVivo()) p1Vivo = true;
    }

    bool p2Vivo = false;
    for (int i = 0; i < 5; i++) {
        Elemento* e = jugador2->obtener_elemento(i);
        if (e && e->estaVivo()) p2Vivo = true;
    }

    // Si el jugador 1 se queda sin vida, gana la IA
    if (!p1Vivo) {
        mensajeGanador = "¡La IA ha ganado la partida!";
        return true;
    }
    // Si la IA se queda sin vida, gana el jugador humano
    if (!p2Vivo) {
        mensajeGanador = "¡Felicitaciones, has ganado la partida!";
        return true;
    }

    return false; // El juego continúa si ambos tienen elementos vivos
}

// Obtiene un resumen completo y formateado del estado actual de los mazos de ambos contrincantes
std::string Partida::obtenerResumen() {
    std::string resumen = "RESUMEN FINAL\n\nTus elementos:\n";
    for (int i = 0; i < 5; i++) {
        Elemento* e = jugador1->obtener_elemento(i);
        if (e) {
            resumen += tipoToString(e->obtener_tipo()) + ": " + std::to_string(e->obtener_vida()) + " de vida\n";
        }
    }

    resumen += "\nElementos de la IA:\n";
    for (int i = 0; i < 5; i++) {
        Elemento* e = jugador2->obtener_elemento(i);
        if (e) {
            resumen += tipoToString(e->obtener_tipo()) + ": " + std::to_string(e->obtener_vida()) + " de vida\n";
        }
    }
    return resumen;
}