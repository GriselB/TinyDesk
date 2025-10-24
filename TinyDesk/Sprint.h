#pragma once
#include <string>
#include "Fecha.h"
#include "Estado.h"
#include "area.h"


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
    void setIdProyecto(int idProyecto);
    void setIdSprint(int idTicket);
    void setStatus(std::string status);
    void setIdArea(int idArea);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();

private:
    int _idProyecto;
    int _idSprint;
    int  _idArea;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    char _status[20];
};
