#pragma once
#include <string>

class Estado
{
public:
    int getIdEstado();
    std::string getNombreEstado(int n);
    void setIdEstado(int idEstado);
    void mostrar();
    void seleccionarEstado();
private:
    int _idEstado;
    const char *_nombres[3] = {
    "No Disponible","Disponible","Finalizado"
    };
};
