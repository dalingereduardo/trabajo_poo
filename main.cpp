#include "interfaz.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);
    interfaz w; // 'interfaz' con 'i' minúscula
    w.show();

    return a.exec();
}