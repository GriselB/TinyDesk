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
    int  _idArea;
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
    int getIdArea();
    std::string getStatus();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    Fecha getFechaFinalizada();
    bool getActivo();
    
    //setters
    void setIdProyecto(int idProyecto);
    void setIdSprint(int idTicket);
    void setStatus(std::string status);
    //void setNombre(std::string nombre);
    void setNombre(const std::string &nombre);
    void setIdArea(int idArea);
    void setFechaInicio(const Fecha &f);
    void setFechaFin(const Fecha &f);
    void setFechaFinalizada();
    bool setActivo(bool activo);
};

