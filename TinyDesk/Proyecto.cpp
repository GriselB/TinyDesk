#include <cstring>
#include <iostream>
#include "Proyecto.h"
#include "Fecha.h"
#include "utils.h"

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
void Proyecto::cargar()
{
    std::string nombre, descripcion;
    int idEstado;
    Fecha inicio,fin,finalizada;
    std::cout<<"Ingrese un nombre de proyecto: ";
    setNombre(nombre);
    setDescripcion(descripcion);
    inicio=Fecha("inicio");
    fin=Fecha("fin");
    finalizada=Fecha("finalizada");
    idEstado=1;
}
void Proyecto::mostrar()
{
    std::cout<<"Id del proyecto: "<<getIdProyecto()<<std::endl;
    std::cout<<"Nombre del proyecto: "<<getNombre()<<std::endl;
    std::cout<<"Descripción del proyecto: "<<getDescripcion()<<std::endl;
    std::cout<<"Fecha de inicio del proyecto: "<<getFechaInicio().toString()<<std::endl;
    std::cout<<"Fecha de fin del proyecto: "<<getFechaFin().toString()<<std::endl;
    std::cout<<"Fecha de finalización del proyecto: "<<getFechaFinalizada().toString()<<std::endl;
    std::cout<<"Id del estado del proyecto: "<<getIdEstado()<<std::endl;
}
