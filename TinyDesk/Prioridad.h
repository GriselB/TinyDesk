#pragma once
#include <string>

class Prioridad
{
public:
    int getIdPrioridad();
    std::string getDescripcionPrioridad(int n);
    void setIdPrioridad(int idPrioridad);
    void mostrar();
    void seleccionarPrioridad();
private:
    int _idPrioridad;
    const char *_descripcion[3] = {
    "Baja","Media","Alta"
    };
};
