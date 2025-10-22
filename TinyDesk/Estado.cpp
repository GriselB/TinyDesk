#include <cstring>
#include "Estado.h"

int Estado::getIdEstado()
{
    return _idEstado;
}
std::string Estado::getNombre()
{
    return _nombre;
}

int Estado::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}
std::string Estado::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}
