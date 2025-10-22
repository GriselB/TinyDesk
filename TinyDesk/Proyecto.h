#pragma once
#include <string>
#include "Fecha.h"

class Proyecto
{
public:
    int getIdProyecto();
    std::string getNombre();
    std::string getDescripcion();
    Fecha getFechaInicio();
    Fecha getFechaFin();
    int getIdEstado();
    Fecha getFechaFinalizada();
    int setIdProyecto(int idProyecto);
    std::string setNombre(std::string nombre);
    std::string setDescripcion(std::string descripcion);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();
    int setIdEstado(int idEstado);
private:
    int _idProyecto;
    char _nombre[50];
    char _descripcion[250];
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    int _idEstado;
};
