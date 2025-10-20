#pragma once
#include <string>
#include "Fecha.h"

class Ticket
{
public:
    int getIdEmpleado();
    int getIdTicket();
    std::string getStatus();
    std::string getPrioridad();
    std::string getDescripcionTarea();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    void setIdEmpleado(int idEmpleado);
    void setIdTicket(int idTicket);
    void setStatus(std::string status);
    void setPrioridad(std::string prioridad);
    void setDescripcionTarea(std::string descripcionTarea);
    void setFechaInicio();
    void setFechaFin(Fecha fecha);

private:
    int _idEmpleado;
    int _idTicket;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    char _status[20];
    char _prioridad[20];
    char _descripcionTarea[250];
};
