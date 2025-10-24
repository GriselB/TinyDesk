#include <cstring>
#include "Area.h"

int Area::getIdArea()
{
    return _idArea;
}
std::string Area::getNombre()
{
    return _nombre;
}

int Area::setIdArea(int idArea)
{
    _idArea=idArea;
}
std::string Area::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}
