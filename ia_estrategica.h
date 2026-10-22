#ifndef IA_ESTRATEGICA_H
#define IA_ESTRATEGICA_H
#include "ia.h"

class IA_estrategica: public IA
{
public:
    IA_estrategica();
    ~IA_estrategica();
    Elemento* seleccionar_elemento() override;
};

#endif // IA_ESTRATEGICA_H
