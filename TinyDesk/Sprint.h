#pragma once
#include <string>
#include "Fecha.h"
#include "Estado.h"
#include "Area.h"
#include "Proyecto.h"

class Sprint {
private:
    int _idProyecto;
    int _idSprint;
    Area _area;
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    char _status[20];
    char _nombre[50];
    bool  _activo;
    int _idEstado;
    Proyecto _proyecto;
    
public:

    
    //getters
    std::string getNombre();
    int getIdSprint();
    int getIdProyecto();
    Area getArea();
    int getIdEstado();
    std::string getFechaInicio();
    std::string getFechaFin();
    std::string getFechaFinalizada();
   
    
    //setters
    void setIdProyecto(int idProyecto);
    void setIdSprint(int idTicket);
    void setIdEstado(int idEstado);
    void setNombre(const std::string &nombre);
    void setArea(const Area &a);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();
};



