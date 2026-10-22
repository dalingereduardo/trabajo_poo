#ifndef HUMANO_H
#define HUMANO_H
#include "jugador.h"

class Humano: public Jugador
{
public:
    Humano();
    ~Humano();
    Elemento* seleccionar_elemento();

};

#endif // HUMANO_H
