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

Fecha Ticket::getFechaInicio()
{
    _fechaInicio.toString();
}

Fecha Ticket::getFechaFin()
{
    _fechaFin.toString();
}

void Ticket::setFechaInicio()
{
    int dia,mes,anio;

    std::cout << "Ingrese día de inicio: ";
    std::cin >> dia;
    std::cout << "Ingrese mes de inicio: ";
    std::cin >> mes;
    std::cout << "Ingrese año de inicio: ";
    std::cin >> anio;
    _fechaInicio.setDia(dia);
    _fechaInicio.setMes(mes);
    _fechaInicio.setAnio(anio);
}

void Ticket::setFechaFin(Fecha fecha)
{
    int dia,mes,anio;
    std::cout << "Ingrese día de fin: ";
    std::cin >> dia;
    std::cout << "Ingrese mes de fin: ";
    std::cin >> mes;
    std::cout << "Ingrese año de fin: ";
    std::cin >> anio;
    _fechaFin.setDia(dia);
    _fechaFin.setMes(mes);
    _fechaFin.setAnio(anio);
}
