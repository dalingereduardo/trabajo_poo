#ifndef IA_H
#define IA_H
#include "jugador.h"

class IA: public Jugador
{
public:
    IA();
    virtual ~IA();
    virtual Elemento* seleccionar_elemento()= 0;

};

#endif // IA_H
