#include <cstring>
#include <iostream>
#include "Sprint.h"
#include "Fecha.h"
#include "Proyecto.h"
#include "area.h"
#include "Estado.h"
#include "utils.h"

using namespace std;



// get

string Sprint::getNombre() 
{ 
  return string(_nombre);   
}

string Sprint::getProyectoDelSprint() 
{ 
  return string(_nombreProyecto);   
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
  

Fecha  Sprint::getFechaInicio()
{
    return _fechaInicio;
}

Fecha  Sprint::getFechaFin()
{
    return _fechaFin;
}

Fecha Sprint::getFechaFinalizada()
{
    return _fechaFinalizada;
}



// Setters

void Sprint::setNombre(const std::string &nombre)
{
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

void Sprint::setProyectoDelSprint(const std::string &nombreProyecto)
{
    strncpy(_nombreProyecto, nombreProyecto.c_str(), 49);
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

void Sprint::setFechaInicio(Fecha f) {
    _fechaInicio = f;
}

void Sprint::setFechaFin(Fecha f) {
    _fechaFin = f;
}


