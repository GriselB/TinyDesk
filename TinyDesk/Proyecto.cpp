#include <cstring>
#include <iostream>
#include "Proyecto.h"
#include "Fecha.h"

int Proyecto::getIdProyecto()
{
    return _idProyecto;
}

std::string Proyecto::getNombre()
{
    return _nombre;
}

std::string Proyecto::getDescripcion()
{
    return _descripcion;
}

Fecha Proyecto::getFechaInicio()
{
    return _fechaInicio.toString();
}

Fecha Proyecto::getFechaFin()
{
    return _fechaFin.toString();
}

Fecha Proyecto::getFechaFinalizada()
{
    return _fechaFinalizada.toString();
}

int Proyecto::getIdEstado()
{
    return _idEstado;
}

void Proyecto::setIdProyecto(int idProyecto)
{
    _idProyecto=idProyecto;
}

void Proyecto::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

void Proyecto::setDescripcion(std::string descripcion)
{
    strncpy(_descripcion, descripcion.c_str(), 249);
    _descripcion[249] = '\0';
}

void Proyecto::setFechaInicio()
{
    _fechaInicio = Fecha("inicio");
}

void Proyecto::setFechaFin()
{
    _fechaFin = Fecha("fin");
}

void Proyecto::setFechaFinalizada()
{
    _fechaFinalizada = Fecha("finalizacion");
}

void Proyecto::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}
