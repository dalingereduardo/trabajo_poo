#ifndef IA_ALEATORIA_H
#define IA_ALEATORIA_H
#include "ia.h"

// Definición de la clase IA_aleatoria que hereda de la clase abstracta IA (implementa el comportamiento de un oponente controlado por la computadora que elige su elemento al azar)
class IA_aleatoria: public IA
{
public:
    // Constructor de la clase IA_aleatoria
    IA_aleatoria();

    // Destructor de la clase IA_aleatoria
    ~IA_aleatoria();

    // Sobrescribe (override) el método virtual puro de la clase base para definir la lógica donde la IA selecciona un elemento de manera aleatoria
    Elemento* seleccionar_elemento() override;

};

#endif // IA_ALEATORIA_H