#include <cstring>
#include <iostream>
#include "Ticket.h"
#include "Fecha.h"

int Ticket::getIdEmpleado()
{
    return _idEmpleado;
}

std::sting Ticket::getNombreEmpleado(){
    return string(_nombreEmpleado);
}

int Ticket::getIdTicket()
{
    return _idTicket;
}

int Ticket::getIdSprint(){
    return _idSprint;
}

std::sting Ticket::getNombreSprint(){
    return string(_nombreSprint);
}

int Ticket::getIdProyecto(){
    return _idProyecto;
}

std::sting Ticket::getNombreProyecto(){
    return string(_nombreProyecto);
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

void Ticket::setNombreEmpleado(std::str nombreEmpleado){
    strncpy(_nombreEmpleado, nombreEmpleado.c_str(), 49);
    _nombre[49] = '\0';
}

void Ticket::setIdTicket(int idTicket)
{
    _idTicket=idTicket;
}

void Ticket::setIdSprint(int idSprint){
    _idSprint = idSprint;
}

void Ticket::setNombreSprint(std::str nombreSprint){
    strncpy(_nombreSprint, nombreSprint.c_str(), 49);
    _nombre[49] = '\0';
}

void Ticket::setIdProyecto(int idProyecto){
    _idProyecto = idProyecto;
}

void Ticket::setNombreProyecto(std::str nombreProyecto){
    strncpy(_nombreProyecto, nombreProyecto.c_str(), 49);
    _nombre[49] = '\0';
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

