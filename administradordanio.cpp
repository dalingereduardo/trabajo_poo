#include "administradordanio.h"
#include <fstream>
#include <sstream>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

AdministradorDanio::AdministradorDanio() {
    // Inicializar por defecto con 20 por seguridad
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz_danio[i][j] = 20;
        }
    }

    // Buscar el archivo config.txt en la carpeta del ejecutable (.exe) y rutas alternativas
    QString rutaExe = QCoreApplication::applicationDirPath();
    QString rutaConfig1 = QDir(rutaExe).filePath("config.txt");
    QString rutaConfig2 = "../config.txt";
    QString rutaConfig3 = "config.txt";

    if (cargarConfiguracion(rutaConfig1.toStdString())) {
        // Encontrado al lado del .exe
    } else if (cargarConfiguracion(rutaConfig2.toStdString())) {
        // Encontrado un nivel arriba
    } else if (cargarConfiguracion(rutaConfig3.toStdString())) {
        // Encontrado en el directorio local
    } else {
        qDebug() << "[AVISO] No se encontró config.txt. Usando daño por defecto (20).";
    }
}

bool AdministradorDanio::cargarConfiguracion(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) return false;

    std::string linea;
    int fila = 0;
    while (std::getline(archivo, linea) && fila < 4) {
        if (linea.empty() || linea[0] == '#' || linea[0] == '/') continue; // Ignorar comentarios

        std::stringstream ss(linea);
        int val;
        int col = 0;
        while (ss >> val && col < 4) {
            matriz_danio[fila][col] = val;
            col++;
        }
        if (col == 4) {
            fila++;
        }
    }
    archivo.close();
    qDebug() << "[EXITO] Matriz de daño cargada correctamente desde:" << QString::fromStdString(rutaArchivo);
    return true;
}

int AdministradorDanio::obtener_danio(int atacante, int defensor) const {
    if (atacante >= 0 && atacante < 4 && defensor >= 0 && defensor < 4) {
        return matriz_danio[atacante][defensor];
    }
    return 20;
}