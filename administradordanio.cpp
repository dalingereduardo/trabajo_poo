#include "administradordanio.h"
#include <fstream>
#include <sstream>
#include <QDebug>
#include <QCoreApplication>
#include <QDir>

// Constructor de la clase AdministradorDanio: inicializa la matriz y busca el archivo de configuración externo
AdministradorDanio::AdministradorDanio() {
    // Inicializa por defecto toda la matriz de 4x4 con un valor de daño de 20 por seguridad
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matriz_danio[i][j] = 20;
        }
    }

    // Obtiene la ruta del directorio donde se encuentra el ejecutable (.exe) y define rutas alternativas de búsqueda
    QString rutaExe = QCoreApplication::applicationDirPath();
    QString rutaConfig1 = QDir(rutaExe).filePath("config.txt"); // Ruta junto al .exe
    QString rutaConfig2 = "../config.txt";                      // Ruta un nivel arriba en directorios
    QString rutaConfig3 = "config.txt";                         // Ruta local por defecto

    // Intenta cargar el archivo de configuración probando secuencialmente las distintas rutas posibles
    if (cargarConfiguracion(rutaConfig1.toStdString())) {
        // Archivo encontrado y cargado correctamente al lado del .exe
    } else if (cargarConfiguracion(rutaConfig2.toStdString())) {
        // Archivo encontrado un nivel arriba
    } else if (cargarConfiguracion(rutaConfig3.toStdString())) {
        // Archivo encontrado en el directorio local
    } else {
        // Si no se encuentra en ninguna ubicación, emite un aviso por consola y mantiene los valores por defecto
        qDebug() << "[AVISO] No se encontró config.txt. Usando daño por defecto (20).";
    }
}

// Método privado para leer el archivo de texto y volcar los valores numéricos en la matriz de daño
bool AdministradorDanio::cargarConfiguracion(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo); // Abre el archivo en modo lectura
    if (!archivo.is_open()) return false; // Retorna falso si el archivo no pudo abrirse

    std::string linea;
    int fila = 0;
    // Lee el archivo línea por línea asegurándose de no superar las 4 filas de la matriz
    while (std::getline(archivo, linea) && fila < 4) {
        // Ignora las líneas vacías o aquellas que comiencen con símbolos de comentario (# o /)
        if (linea.empty() || linea[0] == '#' || linea[0] == '/') continue;

        std::stringstream ss(linea);
        int val;
        int col = 0;
        // Extrae los valores numéricos separados por espacios de la línea actual (hasta 4 columnas)
        while (ss >> val && col < 4) {
            matriz_danio[fila][col] = val;
            col++;
        }
        // Si se completaron las 4 columnas de la fila, avanza a la siguiente fila
        if (col == 4) {
            fila++;
        }
    }
    archivo.close(); // Cierra el archivo tras finalizar la lectura
    qDebug() << "[EXITO] Matriz de daño cargada correctamente desde:" << QString::fromStdString(rutaArchivo);
    return true; // Retorna true indicando que la carga fue exitosa
}

// Método público para consultar el valor de daño específico entre un elemento atacante y uno defensor
int AdministradorDanio::obtener_danio(int atacante, int defensor) const {
    // Valida que los índices del atacante y el defensor se encuentren dentro del rango válido de la matriz (0 a 3)
    if (atacante >= 0 && atacante < 4 && defensor >= 0 && defensor < 4) {
        return matriz_danio[atacante][defensor]; // Retorna el valor de daño correspondiente
    }
    return 20; // Retorna un valor de daño por defecto (20) si los índices están fuera de rango
}