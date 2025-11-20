#include <cstring>
#include <iostream>
#include "Ticket.h"
#include "Fecha.h"

int Ticket::getIdEmpleado()
{
    return _idEmpleado;
}

int Ticket::getIdTicket()
{
    return _idTicket;
}

int Ticket::getIdSprint(){
    return _idSprint;
}

int Ticket::getIdProyecto(){
    return _idProyecto;
}

int Ticket::getStatus()
{
    return _status;
}

std::string Ticket::getPrioridad()
{
    return _prioridad;
}

std::string Ticket::getDescripcionTarea()
{
    return _descripcionTarea;
}

Fecha Ticket::getFechaInicio()
{
    return _fechaInicio;
}

Fecha Ticket::getFechaFin()
{
    return _fechaFin;
}

Fecha Ticket::getFechaFinalizada()
{
    return _fechaFinalizada;
}

void Ticket::setIdEmpleado(int idEmpleado)
{
    _idEmpleado=idEmpleado;
}

void Ticket::setIdTicket(int idTicket)
{
    _idTicket=idTicket;
}

void Ticket::setIdSprint(int idSprint){
    _idSprint = idSprint;
}

void Ticket::setIdProyecto(int idProyecto){
    _idProyecto = idProyecto;
}

void Ticket::setStatus(int status)
{
    _status = status;
}

void Ticket::setPrioridad(std::string prioridad)
{
    strncpy(_prioridad, prioridad.c_str(), 19);
    _prioridad[19] = '\0';
}

void Ticket::setDescripcionTarea(std::string descripcionTarea)
{
    strncpy(_descripcionTarea, descripcionTarea.c_str(), 249    );
    _descripcionTarea[249] = '\0';
}

void Ticket::setFechaInicio(Fecha fecha)
{
    _fechaInicio = fecha;
}

void Ticket::setFechaFin(Fecha fecha)
{
    _fechaFin = fecha;
}

void Ticket::setFechaFinalizada(Fecha fecha)
{
    _fechaFinalizada = fecha;
}

