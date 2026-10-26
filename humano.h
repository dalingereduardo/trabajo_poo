#ifndef HUMANO_H
#define HUMANO_H
#include "jugador.h"

// Definición de la clase Humano que hereda de la clase base Jugador (polimorfismo)
class Humano: public Jugador
{
public:
    // Constructor de la clase Humano para inicializar al jugador controlado por el usuario
    Humano();

    // Destructor de la clase Humano
    ~Humano();

    // Método sobrescrito (override) que permite al jugador humano seleccionar manualmente su elemento de combate
    Elemento* seleccionar_elemento();

};

#endif // HUMANO_H