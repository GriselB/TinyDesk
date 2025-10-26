#include <cstring>
#include "area.h"

int Area::getIdArea()
{
    return _idArea;
}
std::string Area::getNombre()
{
    return _nombre;
}

void Area::setIdArea(int idArea)
{
    _idArea=idArea;
}
void Area::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}
