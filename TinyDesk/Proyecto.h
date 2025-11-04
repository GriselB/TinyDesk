#pragma once
#include <string>
#include "Fecha.h"

class Proyecto
{
public:
    int getIdProyecto();
    std::string getNombre();
    std::string getDescripcion();
    std::string getFechaInicio();
    std::string getFechaFin();
    std::string getFechaFinalizada();
    int getIdEstado();
    void setIdProyecto(int idProyecto);
    void setNombre(std::string nombre);
    void setDescripcion(std::string descripcion);
    void setFechaInicio();
    void setFechaFin();
    void setFechaFinalizada();
    void setIdEstado(int idEstado);
    void cargar();
    void mostrar();
private:
    int _idProyecto;
    char _nombre[50];
    char _descripcion[250];
    Fecha _fechaInicio;
    Fecha _fechaFin;
    Fecha _fechaFinalizada;
    int _idEstado;
};
