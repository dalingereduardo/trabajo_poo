#ifndef JUGADOR_H
#define JUGADOR_H

#include "elemento.h"

// Definición de la clase base polimórfica 'Jugador' que representa a cualquier participante del juego
class Jugador
{
protected:
    Elemento* elementos[5]; // Arreglo estático de punteros que representa el mazo o conjunto de cinco cartas/elementos del jugador

public:
    // Constructor de la clase base Jugador
    Jugador();

    // Destructor virtual: obligatorio en clases base polimórficas para garantizar una correcta destrucción de los objetos derivados
    virtual ~Jugador();

    // Método virtual puro (= 0): convierte a la clase en abstracta y obliga a las subclases (Humano e IA) a implementar su propia lógica de selección de elementos
    virtual Elemento* seleccionar_elemento() = 0;

    // Método para consultar la cantidad de cartas o elementos que le quedan con vida al jugador
    int cantidad_cartas();

    // Método para permitir que la clase Partida asigne o cargue nuevas cartas en una posición específica del mazo
    void asignar_carta(int indice, Elemento* nueva_carta);

    // Método en línea (inline) y selector (getter) para consultar un elemento específico del mazo de acuerdo a su índice de manera segura
    Elemento* obtener_elemento(int indice) {
        // Verifica que el índice se encuentre dentro de los límites válidos del mazo (de 0 a 4)
        if (indice >= 0 && indice < 5) {
            return elementos[indice]; // Retorna el puntero al elemento si el índice es válido
        }
        return nullptr; // Retorna nullptr si el índice está fuera de rango para evitar errores de memoria
    }
};

#endif // JUGADOR_H