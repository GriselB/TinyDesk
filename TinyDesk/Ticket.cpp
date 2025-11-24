#include <cstring>
#include <iostream>
#include "Ticket.h"
#include "Fecha.h"

int Ticket::getIdEmpleado()
{
    return _idEmpleado;
}

std::string Ticket::getNombreEmpleado(){
    return (_nombreEmpleado);
}

int Ticket::getIdTicket()
{
    return _idTicket;
}

int Ticket::getIdSprint(){
    return _idSprint;
}

std::string Ticket::getNombreSprint(){
    return _nombreSprint;
}

int Ticket::getIdProyecto(){
    return _idProyecto;
}

std::string Ticket::getNombreProyecto(){
    return _nombreProyecto;
}

Estado Ticket::getStatus()
{
    return _status;
}

Prioridad Ticket::getPrioridad()
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

void Ticket::setNombreEmpleado(std::string nombreEmpleado){
    strncpy(_nombreEmpleado, nombreEmpleado.c_str(), 49);
    _nombreEmpleado[49] = '\0';
}

void Ticket::setIdTicket(int idTicket)
{
    _idTicket=idTicket;
}

void Ticket::setIdSprint(int idSprint){
    _idSprint = idSprint;
}

void Ticket::setNombreSprint(std::string nombreSprint){
    strncpy(_nombreSprint, nombreSprint.c_str(), 49);
    _nombreSprint[49] = '\0';
}

void Ticket::setIdProyecto(int idProyecto){
    _idProyecto = idProyecto;
}

void Ticket::setNombreProyecto(std::string nombreProyecto){
    strncpy(_nombreProyecto, nombreProyecto.c_str(), 49);
    _nombreProyecto[49] = '\0';
}


void Ticket::setStatus(Estado status)
{
    _status = status;
}

void Ticket::setPrioridad(Prioridad prioridad)
{
   _prioridad = prioridad;
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

