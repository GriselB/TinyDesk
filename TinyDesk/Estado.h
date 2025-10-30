#pragma once
#include <string>

class Estado
{
public:
    int getIdEstado();
    std::string getNombre();
    void setIdEstado(int idEstado);
    void setNombre(std::string nombre);
    void mostrar();
    void seleccionarEstado();
private:
    int _idEstado;
    char _nombre[20];
};
