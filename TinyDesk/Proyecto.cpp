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
    _fechaInicio.toString();
}

Fecha Proyecto::getFechaFin()
{
    _fechaFin.toString();
}

Fecha Proyecto::getFechaFinalizada()
{
    _fechaFinalizada.toString();
}

int Proyecto::getIdEstado()
{
    return _idEstado;
}

int Proyecto::setIdProyecto(int idProyecto)
{
    _idProyecto=idProyecto;
}

std::string Proyecto::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

std::string Proyecto::setDescripcion(std::string descripcion)
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

int Proyecto::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}
