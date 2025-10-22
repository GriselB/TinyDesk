#pragma once
#include <string>
#include "Fecha.h"
#include "Estado.h"
#include "Area.h"


class Sprint
{
public:
    int getIdSprint();
    int getIdProyecto();
    int getIdArea();
    std::string getStatus();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();
    void setIdEmpleado(int idEmpleado);
    void setIdSprint(int idTicket);
    void setStatus(std::string status);
    void setArea(int idArea)
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();

private:
    int _idEmpleado;
    int _idSprint;
    int  _idArea;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    char _status[20];
};
