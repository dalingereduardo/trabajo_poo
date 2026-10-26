#include "elemento.h"

// Constructor de la clase Elemento: inicializa los puntos de vida y el tipo de elemento mediante la lista de inicialización
Elemento::Elemento(int _vida, TipoElemento _tipo) : vida(_vida), tipo(_tipo) {}

// Destructor de la clase Elemento (cuerpo vacío ya que no requiere liberación dinámica manual de memoria en este nivel)
Elemento::~Elemento(){

}

// Método para reducir los puntos de vida del elemento según el daño recibido
void Elemento::recibirDanio(int valor) {
    vida -= valor; // Resta el valor del daño a la vida actual
    if (vida < 0) {
        vida = 0; // Si la vida resultante es menor a 0, se establece en 0 para evitar valores negativos
    }
}

// Método para verificar si el elemento sigue con vida (retorna true si la vida es estrictamente mayor a 0)
bool Elemento::estaVivo() {
    return vida > 0;
}

// Método selector (getter) para consultar el tipo de elemento
TipoElemento Elemento::obtener_tipo() {
    return tipo;
}

// Método selector (getter) para consultar los puntos de vida actuales
int Elemento::obtener_vida() {
    return vida;
}