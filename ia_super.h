#ifndef IA_SUPER_H
#define IA_SUPER_H

#include "ia.h"
#include "administradordanio.h"

// Definición de la clase IA_super que hereda de la clase base IA (implementa el nivel de inteligencia artificial más avanzado, capaz de evaluar el estado del oponente y las reglas de daño)
class IA_super : public IA {
public:
    // Constructor de la clase IA_super
    IA_super();

    // Destructor de la clase IA_super
    ~IA_super();

    // Método sobrecargado principal para la Super IA: recibe el elemento actual del jugador humano y el administrador de daños para calcular la mejor estrategia de contraataque
    Elemento* seleccionar_elemento(Elemento* elementoHumano, AdministradorDanio& adminDanio);

    // Sobrescribe el método virtual puro heredado por compatibilidad con la clase base, devolviendo por defecto la primera opción viva disponible si no se usa el método avanzado
    Elemento* seleccionar_elemento() override;
};

#endif