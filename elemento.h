#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <string>

// Enumeración fuertemente tipada (enum class) para definir los 4 elementos del juego con sus valores numéricos asociados
enum class TipoElemento {
    AGUA = 0,
    TIERRA = 1,
    FUEGO = 2,
    AIRE = 3
};

// Función auxiliar en línea para convertir un valor de TipoElemento a su representación en texto (std::string)
inline std::string tipoToString(TipoElemento tipo) {
    switch (tipo) {
    case TipoElemento::AGUA:   return "Agua";
    case TipoElemento::TIERRA: return "Tierra";
    case TipoElemento::FUEGO:  return "Fuego";
    case TipoElemento::AIRE:   return "Aire";
    default:                   return "Elemento";
    }
}

// Definición de la clase base polimórfica 'Elemento' que representa a los combatientes
class Elemento
{
protected:
    int vida;          // Almacena los puntos de vida actuales del elemento
    TipoElemento tipo; // Almacena el tipo de elemento correspondiente (Agua, Tierra, Fuego o Aire)

public:
    // Constructor que inicializa la vida y el tipo del elemento
    Elemento(int _vida, TipoElemento _tipo);

    // Destructor virtual: obligatorio en clases base para garantizar la correcta destrucción de los objetos derivados
    virtual ~Elemento();

    // Método para restar vida al elemento en función del daño recibido
    void recibirDanio(int valor);

    // Método para verificar si el elemento sigue con vida (retorna true si la vida es mayor a 0)
    bool estaVivo();

    // Método de consulta (getter) para obtener los puntos de vida actuales
    int obtener_vida();

    // Método de consulta (getter) para obtener el tipo de elemento
    TipoElemento obtener_tipo();
};

#endif // ELEMENTO_H