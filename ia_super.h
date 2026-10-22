#ifndef IA_SUPER_H
#define IA_SUPER_H

#include "ia.h"
#include "administradordanio.h"

class IA_super : public IA {
public:
    IA_super();
    ~IA_super();

    // Método principal para la Super IA pasándole el objetivo y la matriz de daño
    Elemento* seleccionar_elemento(Elemento* elementoHumano, AdministradorDanio& adminDanio);

    // Mantenemos la firma heredada por compatibilidad devolviendo la primera viva
    Elemento* seleccionar_elemento() override;
};

#endif