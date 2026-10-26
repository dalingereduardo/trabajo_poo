#include "interfaz.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

// Función principal (punto de entrada) de la aplicación de escritorio en Qt
int main(int argc, char *argv[])
{
    // Inicializa la semilla para el generador de números pseudoaleatorios utilizando el tiempo actual del sistema
    srand(time(0));

    // Inicializa el objeto principal de la aplicación Qt, encargado de gestionar el bucle de eventos y el ciclo de vida de la GUI
    QApplication a(argc, argv);

    // Instancia la ventana principal del juego correspondiente a la clase 'interfaz'
    interfaz w; // 'interfaz' con 'i' minúscula

    // Hace visible la ventana principal en la pantalla del usuario
    w.show();

    // Inicia el bucle de ejecución de la aplicación Qt y retorna el código de salida al cerrar la ventana
    return a.exec();
}