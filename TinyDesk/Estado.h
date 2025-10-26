#pragma once
#include <string>

class Estado
{
public:
    int getIdEstado();
    std::string getNombre();
    void setIdEstado(int idEstado);
    void setNombre(std::string nombre);
private:
    int _idEstado;
    char _nombre[20];
};
