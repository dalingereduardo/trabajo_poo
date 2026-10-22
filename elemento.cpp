/*#include "elemento.h"

Elemento::Elemento(int _vida, int _tipo): vida(_vida), tipo(_tipo) {}

Elemento::~Elemento() {}

void Elemento::atacar(Elemento *defensor, AdministradorDanio *admin){

    if (!estaVivo() || !defensor->estaVivo()) { //si el atacante o el defensor no estan vivos no se ejecuta nada

        return;

    }

    int porcentajeDanio= admin->obtener_danio(tipo, defensor->obtener_tipo()); //calculamos el daño que va a recibir el defensor

    defensor->recibirDanio(porcentajeDanio); //le aplica el daño al defensor

}

void Elemento::recibirDanio(int valor) {

    vida-=valor; //el daño que recibe cuando es defensor se aplica aca

    if (vida<0) {

        vida= 0;

    }

}

bool Elemento::estaVivo() {

    return vida> 0; //si la vida es mayor a cero esta vivo

}

int Elemento::obtener_tipo() {

    return tipo;

}

int Elemento::obtener_vida() {

    return vida;

}*/
#include "elemento.h"

Elemento::Elemento(int _vida, TipoElemento _tipo) : vida(_vida), tipo(_tipo) {}

Elemento::~Elemento(){

}

void Elemento::recibirDanio(int valor) {
    vida -= valor;
    if (vida < 0) {
        vida = 0;
    }
}

bool Elemento::estaVivo() {
    return vida > 0;
}

TipoElemento Elemento::obtener_tipo() {
    return tipo;
}

int Elemento::obtener_vida() {
    return vida;
}















