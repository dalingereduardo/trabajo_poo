#ifndef IA_H
#define IA_H
#include "jugador.h"

// Definición de la clase abstracta IA que hereda de la clase base Jugador (representa a los jugadores controlados por la computadora)
class IA: public Jugador
{
public:
    // Constructor de la clase IA
    IA();

    // Destructor virtual: necesario para permitir el polimorfismo y la correcta limpieza de memoria en clases derivadas
    virtual ~IA();

    // Método virtual puro (= 0): convierte a esta clase en abstracta y obliga a las subclases de IA (ej. IA fácil, difícil) a implementar su propia lógica de selección
    virtual Elemento* seleccionar_elemento()= 0;

};

#endif // IA_H