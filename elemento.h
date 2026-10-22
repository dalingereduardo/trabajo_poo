/*#ifndef ELEMENTO_H
#define ELEMENTO_H
#include "administradordanio.h"
//clase padre de las clases tierra, agua y fuego.

//Constantes para la matriz.
const int TIPO_AGUA= 0;
const int TIPO_TIERRA= 1;
const int TIPO_FUEGO= 2;

class Elemento
{
protected:
    int vida;
    int tipo; //0 para agua, 1 para tierra, 2 para fuego.

public:
    Elemento(int _vida, int tipo);
    virtual ~Elemento();
    virtual void atacar(Elemento* defensor, AdministradorDanio* admin); //metodo para atacar
    virtual void recibirDanio(int valor); //metodo que le avisa cuanto danio recibio luego de que lo ataquen
    bool estaVivo(); //metodo para saber si le queda vida luego de cada ronda
    int obtener_vida();
    int obtener_tipo();

};

#endif // ELEMENTO_H*/
#ifndef ELEMENTO_H
#define ELEMENTO_H

// Usamos enum class como pidió el profesor para tipar los elementos
enum class TipoElemento {
    AGUA = 0,
    TIERRA = 1,
    FUEGO = 2,
    AIRE = 3,
};

class Elemento
{
protected:
    int vida;
    TipoElemento tipo;

public:
    Elemento(int _vida, TipoElemento _tipo);
    virtual ~Elemento(); // Destructor virtual obligatorio en clases base polimórficas

    void recibirDanio(int valor); // Solo recibe daño, el ataque se maneja en Partida
    bool estaVivo();
    int obtener_vida();
    TipoElemento obtener_tipo();
};

#endif // ELEMENTO_H