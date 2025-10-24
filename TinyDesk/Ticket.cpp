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

std::string Ticket::getStatus()
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
    return _fechaInicio.toString();
}

Fecha Ticket::getFechaFin()
{
    return _fechaFin.toString();
}

void Ticket::setIdEmpleado(int idEmpleado)
{
    _idEmpleado=idEmpleado;
}

void Ticket::setIdTicket(int idTicket)
{
    _idTicket=idTicket;
}

void Ticket::setStatus(std::string status)
{
    strncpy(_status, status.c_str(), 19);
    _status[19] = '\0';
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

void Ticket::setFechaInicio()
{
    _fechaInicio = Fecha("inicio");
}

void Ticket::setFechaFin()
{
    _fechaFin = Fecha("fin");
}

void Ticket::setFechaFinalizada()
{
    _fechaFinalizada = Fecha("finalizacion");
}

