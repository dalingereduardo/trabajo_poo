#ifndef PARTIDA_H
#define PARTIDA_H

#include <string>
#include "jugador.h"
#include "administradordanio.h"

class Partida {
public:
    Partida();
    ~Partida();

    // Métodos públicos
    void inicializar(const std::string& nombreJugador, int tipoIA);
    bool guardarPartida(const std::string& archivo);
    bool cargarPartida(const std::string& archivo);
    void jugarTurno(int indiceElemento);
    bool esFinDeJuego() const;
    std::string obtenerResultadoFinal() const;

    Jugador* getJugador1();
    Jugador* getJugador2();

private:
    void liberar_memoria();
    void repartir_cartas(Jugador* jugador);

    Jugador* jugador1;
    Jugador* jugador2;
    int tipoIA;
    AdministradorDanio adminDanio;
};

#endif // PARTIDA_H