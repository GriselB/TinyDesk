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
    char _nombreProyecto[50];
    bool  _activo;
    int _idEstado;
    Proyecto _proyecto;
    
public:

    
    //getters
    std::string getNombre();
    std::string getProyectoDelSprint();
    int getIdSprint();
    int getIdProyecto();
    Area getArea();
    int getIdEstado();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();
   
    
    //setters
    void setIdProyecto(int idProyecto);
    void setIdSprint(int idTicket);
    void setIdEstado(int idEstado);
    void setNombre(const std::string &nombre);
    void setProyectoDelSprint(const std::string &nombre);
    void setArea(const Area &a);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();
    void setFechaInicio(Fecha f); 
    void setFechaFin(Fecha f);
};



