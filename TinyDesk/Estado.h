#pragma once
#include <string>

class Estado
{
public:
    int getIdEstado();
    std::string getNombre();
    int setIdEstado(int idEstado);
    std::string setNombre(std::string nombre);
private:
    int _idEstado;
    char _nombre[20];
};
