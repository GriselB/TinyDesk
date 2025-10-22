#include <cstring>
#include <iostream>
#include "Sprint.h"
#include "Fecha.h"

using namespace std;

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

std::string Sprint::getStatus()
{
    return _status;
}


Fecha Sprint::getFechaInicio()
{
    _fechaInicio.toString();
}

Fecha Sprint::getFechaFin()
{
    _fechaFin.toString();
}

void Sprint::setIdSprint(int idSprint)
{
    _idSprint=idSprint;
}

void Sprint::setIdProyecto(int idProyecto)
{
    _idProyecto=idProyecto;
}

void Sprint::setIdArea(int idArea)
{
    _idArea=idArea;
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
