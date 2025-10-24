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

void Estado::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}
void Estado::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}
