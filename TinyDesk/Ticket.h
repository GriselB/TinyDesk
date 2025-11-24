#pragma once
#include <string>
#include "Fecha.h"
#include "Prioridad.h"
#include "Estado.h"

class Ticket
{
public:
    //Getters
    int getIdEmpleado();
    std::string getNombreEmpleado();
    int getIdTicket();
    int getIdSprint();
    std::string getNombreSprint();
    int getIdProyecto();
    std::string getNombreProyecto();
    Estado getStatus();
    Prioridad getPrioridad();
    std::string getDescripcionTarea();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();

    //Setters
    void setIdEmpleado(int idEmpleado);
    void setNombreEmpleado(std::string nombreEmpleado);
    void setIdTicket(int idTicket);
    void setIdSprint(int idSprint);
    void setNombreSprint(std::string nombreSprint);
    void setIdProyecto (int idProyecto);
    void setNombreProyecto(std::string nombreProyecto);
    void setStatus(Estado status);
    void setPrioridad(Prioridad prioridad);
    void setDescripcionTarea(std::string descripcionTarea);
    void setFechaInicio(Fecha fecha);
    void setFechaFin(Fecha fecha);
    void setFechaFinalizada(Fecha fecha);

private:
    int _idEmpleado;
    char _nombreEmpleado[50];
    int _idTicket;
    int _idSprint;
    char _nombreSprint[50];
    int _idProyecto;
    char _nombreProyecto[50];
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    Estado _status;
    Prioridad _prioridad;
    char _descripcionTarea[250];
};
