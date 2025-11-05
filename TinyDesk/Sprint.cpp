#include <cstring>
#include <iostream>
#include "Sprint.h"
#include "Fecha.h"
#include "Proyecto.h"
#include "area.h"

using namespace std;



// get

string Sprint::getNombre() 
{ 
  return string(_nombre);   
}  

bool Sprint::getActivo() 
{ 
  return _activo; 
}

int Sprint::getIdSprint()
{
    return _idSprint;
}

int Sprint::getIdProyecto()
{
    return _idProyecto;
}

int Sprint::getIdArea()
{
    return _idArea;
}

string Sprint::getStatus()
{
    return string(_status);
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

void Sprint::setIdArea(int idArea)
{
    _idArea = idArea;
}

void Sprint::setStatus(std::string status)
{
    strncpy(_status, status.c_str(), 19);
    _status[19] = '\0';
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

void Sprint::setActivo(bool activo){
    _activo = activo;
}
