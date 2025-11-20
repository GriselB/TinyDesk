#pragma once
#include <string>
#include "Fecha.h"

class Ticket
{
public:
    //Getters
    int getIdEmpleado();
    int getIdTicket();
    int getIdSprint();
    int getIdProyecto();
    int getStatus();
    std::string getPrioridad();
    std::string getDescripcionTarea();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();

    //Setters
    void setIdEmpleado(int idEmpleado);
    void setIdTicket(int idTicket);
    void setIdSprint(int idSprint);
    void setIdProyecto (int idProyecto);
    void setStatus(int status);
    void setPrioridad(std::string prioridad);
    void setDescripcionTarea(std::string descripcionTarea);
    void setFechaInicio(Fecha fecha);
    void setFechaFin(Fecha fecha);
    void setFechaFinalizada(Fecha fecha);

private:
    int _idEmpleado;
    int _idTicket;
    int _idSprint;
    int _idProyecto;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    int _status;
    char _prioridad[20];
    char _descripcionTarea[250];
};
