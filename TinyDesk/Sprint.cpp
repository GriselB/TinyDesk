#include <cstring>
#include <iostream>
#include "Sprint.h"
#include "Fecha.h"
#include "Proyecto.h"
#include "area.h"
#include "Estado.h"

using namespace std;



// get

string Sprint::getNombre() 
{ 
  return string(_nombre);   
}
  
int Sprint::getIdEstado()
{
    return _idEstado;
}

int Sprint::getIdSprint()
{
    return _idSprint;
}

int Sprint::getIdProyecto()
{
    return _idProyecto;
}


Area Sprint::getArea() 
{ 
  return _area; 
}
  

string  Sprint::getFechaInicio()
{
    return _fechaInicio.toString();
}

string  Sprint::getFechaFin()
{
    return _fechaFin.toString();
}

string Sprint::getFechaFinalizada()
{
    return _fechaFinalizada.toString();
}



// Setters

void Sprint::setNombre(const std::string &nombre)
{
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

void Sprint::setIdSprint(int idSprint)
{
    _idSprint = idSprint;
}

void Sprint::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}

void Sprint::setArea(const Area &a) 
{
   _area = a; 
}

void Sprint::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}


void Sprint::setFechaInicio()
{
    _fechaInicio = Fecha("inicio");
}

void Sprint::setFechaFin()
{
    _fechaFin = Fecha("fin");
}

void Sprint::setFechaFinalizada()
{
    _fechaFinalizada = Fecha("finalizacion");
}


