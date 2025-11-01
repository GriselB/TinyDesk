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
    std::string getStatus();
    std::string getPrioridad();
    std::string getDescripcionTarea();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();
    bool getActivo() const;

    //Setters
    void setIdEmpleado(int idEmpleado);
    void setIdTicket(int idTicket);
    void setIdSprint(int idSprint);
    void setStatus(std::string status);
    void setPrioridad(std::string prioridad);
    void setDescripcionTarea(std::string descripcionTarea);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();
    void setActivo(bool activo);

private:
    int _idEmpleado;
    int _idTicket;
    int _idSprint;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    char _status[20];
    char _prioridad[20];
    char _descripcionTarea[250];

    bool _activo = true;
};
