#ifndef IA_ESTRATEGICA_H
#define IA_ESTRATEGICA_H
#include "ia.h"

// Definición de la clase IA_estrategica que hereda de la clase base IA (implementa un oponente controlado por la computadora con una lógica de decisión más avanzada o táctica)
class IA_estrategica: public IA
{
public:
    // Constructor de la clase IA_estrategica
    IA_estrategica();

    // Destructor de la clase IA_estrategica
    ~IA_estrategica();

    // Sobrescribe (override) el método virtual puro para definir la estrategia específica de selección de elementos de esta IA
    Elemento* seleccionar_elemento() override;
};

#endif // IA_ESTRATEGICA_H