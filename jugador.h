#ifndef JUGADOR_H
#define JUGADOR_H

#include "elemento.h"

class Jugador
{
protected:
    Elemento* elementos[5]; // mazo de cinco cartas

public:
    Jugador();
    virtual ~Jugador();
    virtual Elemento* seleccionar_elemento() = 0; // es distinto en humano e IA
    int cantidad_cartas(); // para saber cuantas cartas vivas le quedan
    void asignar_carta(int indice, Elemento* nueva_carta); // para que la clase partida le asigne nuevas cartas

    // Getter para consultar un elemento del mazo por su índice
    Elemento* obtener_elemento(int indice) {
        if (indice >= 0 && indice < 5) {
            return elementos[indice];
        }
        return nullptr;
    }
};

#endif // JUGADOR_H