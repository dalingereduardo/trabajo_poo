#ifndef ADMINISTRADORDANIO_H
#define ADMINISTRADORDANIO_H

#include <string>

class AdministradorDanio {
private:
    int matriz_danio[4][4];
    bool cargarConfiguracion(const std::string& rutaArchivo);

public:
    AdministradorDanio();
    int obtener_danio(int atacante, int defensor) const;
};

#endif // ADMINISTRADORDANIO_H