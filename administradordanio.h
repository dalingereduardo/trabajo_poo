#ifndef ADMINISTRADORDANIO_H
#define ADMINISTRADORDANIO_H

#include <string> // Incluye la librería para manejar cadenas de texto (usada para la ruta del archivo de configuración)

// Definición de la clase encargada de administrar y calcular las reglas de daño entre elementos
class AdministradorDanio {
private:
    // Matriz de 4x4 que almacena los valores de daño o efectividad entre los 4 elementos del juego
    int matriz_danio[4][4];

    // Método privado para leer y cargar los datos de la matriz de daño desde un archivo externo (ej. config.txt)
    bool cargarConfiguracion(const std::string& rutaArchivo);

public:
    // Constructor: inicializa el administrador de daños (generalmente llama a cargarConfiguracion)
    AdministradorDanio();

    // Método público de consulta que devuelve el daño específico entre un elemento atacante y uno defensor
    int obtener_danio(int atacante, int defensor) const;
};

#endif // ADMINISTRADORDANIO_H