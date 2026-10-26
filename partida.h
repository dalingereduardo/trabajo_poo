#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "jugador.h"
#include "administradordanio.h"

// Definición de la clase Partida, encargada de coordinar la lógica central del juego, turnos, reglas de combate, guardado y estado general
class Partida {
public:
    // Constructor de la clase Partida
    Partida();

    // Destructor de la clase Partida (encargado de liberar la memoria dinámica asociada)
    ~Partida();

    // Métodos públicos

    // Inicializa una nueva partida configurando el nombre del jugador humano y el tipo de inteligencia artificial oponente
    void inicializar(const std::string& nombreJugador, int tipoIA);

    // Guarda el estado actual de la partida en un archivo externo (persistencia)
    bool guardarPartida(const std::string& archivo);

    // Carga una partida guardada previamente desde un archivo externo
    bool cargarPartida(const std::string& archivo);

    // Ejecuta la lógica de un turno de combate completo a partir del índice del elemento seleccionado por el usuario
    std::string jugarTurno(int indiceElemento);

    // Verifica si se han cumplido las condiciones de fin de juego (retorna true si algún jugador se queda sin elementos)
    bool esFinDeJuego() const;

    // Retorna una cadena de texto con el resultado final de la partida
    std::string obtenerResultadoFinal() const;

    // Comprueba si el juego terminó y, en caso afirmativo, asigna el mensaje correspondiente del ganador por referencia
    bool juegoTerminado(std::string& mensajeGanador);

    // Obtiene un resumen detallado del estado o desarrollo actual de la partida
    std::string obtenerResumen();

    // Método selector (getter) para obtener el puntero al objeto del jugador 1 (Humano)
    Jugador* getJugador1();

    // Método selector (getter) para obtener el puntero al objeto del jugador 2 (IA)
    Jugador* getJugador2();

private:
    // Método auxiliar privado para liberar de manera segura la memoria dinámica de los jugadores y sus elementos
    void liberar_memoria();

    // Método auxiliar privado para repartir el mazo inicial de cartas a un jugador
    void repartir_cartas(Jugador* jugador);

    Jugador* jugador1;             // Puntero al jugador humano de la partida
    Jugador* jugador2;             // Puntero al jugador controlado por la inteligencia artificial
    int tipoIA;                    // Almacena el identificador o dificultad del tipo de IA seleccionado
    AdministradorDanio adminDanio; // Objeto encargado de administrar las reglas y matriz de daño entre elementos
};

#endif // PARTIDA_H