#ifndef IA_ALEATORIA_H
#define IA_ALEATORIA_H
#include "ia.h"

class IA_aleatoria: public IA
{
public:
    IA_aleatoria();
    ~IA_aleatoria();
    Elemento* seleccionar_elemento() override;

};

#endif // IA_ALEATORIA_H
