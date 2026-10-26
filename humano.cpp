#include "humano.h"
#include <iostream>

using namespace std;

// Constructor de la clase Humano: llama al constructor de la clase base Jugador
Humano::Humano(): Jugador() {}

// Destructor de la clase Humano
Humano::~Humano() {}

// Método para que el jugador humano seleccione manualmente un elemento/carta de su mazo para el combate
Elemento* Humano::seleccionar_elemento() {

    int opcion, indice;
    bool seleccion_valida = false;

    // Bucle que se mantiene activo hasta que el usuario elija una carta válida y disponible
    while (!seleccion_valida) {

        cout<<"\n--Cartas Disponibles---"<<endl;

        // Recorre el mazo de 5 cartas del jugador
        for (int i=0; i<5; i++) {

            // Verifica que la posición no sea nula y que el elemento siga con vida
            if (elementos[i]!=NULL && elementos[i]->estaVivo()) {
                // Evaluamos el tipo para mostrar su nombre en texto en lugar de imprimir el enum class directamente
                TipoElemento t = elementos[i]->obtener_tipo();
                string nombreTipo = (t == TipoElemento::AGUA) ? "Agua" : (t == TipoElemento::TIERRA) ? "Tierra" : "Fuego";

                // Muestra en consola el número de la carta, su tipo y sus puntos de vida actuales
                cout<<i+1<<") Carta tipo: "<<nombreTipo<<" |Vida: "<<elementos[i]->obtener_vida()<<endl;

            }else{
                // Si la carta ya fue destruida o es nula, se muestra como no disponible
                cout<<i+1<<") Carta no disponible/ destruida"<<endl;

            }

        }

        cout<<"Elija el numero de carta a usar (1-5): ";
        cin>>opcion;

        indice = opcion - 1; // Ajusta el índice introducido por el usuario (1-5) a base cero (0-4) para el arreglo

        // Valida que el índice esté dentro del rango del mazo y que la carta elegida exista y esté viva
        if (indice>=0 && indice<5 && elementos[indice]!=NULL && elementos[indice]->estaVivo()) {

            seleccion_valida = true;     // Marca la selección como válida para salir del bucle
            return elementos[indice];    // Retorna el puntero al elemento seleccionado

        }else{
            // Muestra un mensaje de error si la opción ingresada no es válida
            cout<<"Esta carta no es valida, elija otra."<<endl;

        }

    }

    return NULL; // Retorno de seguridad (aunque idealmente siempre retorna desde el if válido)

}