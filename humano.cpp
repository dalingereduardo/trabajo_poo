#include "humano.h"
#include <iostream>

using namespace std;

Humano::Humano(): Jugador() {}

Humano::~Humano() {}

Elemento* Humano::seleccionar_elemento() {

    int opcion, indice;
    bool seleccion_valida= false;

    while (!seleccion_valida) {

        cout<<"\n--Cartas Disponibles---"<<endl;

        for (int i=0; i<5; i++) {

            if (elementos[i]!=NULL && elementos[i]->estaVivo()) {
                // Evaluamos el tipo para mostrar su nombre en texto en lugar de imprimir el enum class directamente
                TipoElemento t = elementos[i]->obtener_tipo();
                string nombreTipo = (t == TipoElemento::AGUA) ? "Agua" : (t == TipoElemento::TIERRA) ? "Tierra" : "Fuego";

                cout<<i+1<<") Carta tipo: "<<nombreTipo<<" |Vida: "<<elementos[i]->obtener_vida()<<endl;

            }else{

                cout<<i+1<<") Carta no disponible/ destruida"<<endl;

            }

        }

        cout<<"Elija el numero de carta a usar (1-5): ";
        cin>>opcion;

        indice= opcion- 1; //ajusto el indice para que sea del 0 al 4

        if (indice>=0 && indice<5 && elementos[indice]!=NULL && elementos[indice]->estaVivo()) {

            seleccion_valida= true;
            return elementos[indice];

        }else{

            cout<<"Esta carta no es valida, elija otra."<<endl;

        }

    }

    return NULL;

}