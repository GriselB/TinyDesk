#pragma once
#include <string>
#include "Proyecto.h"

class ProyectoArchivo
{
public:
    ProyectoArchivo(std::string nombreArchivo = "proyectos.dat");
    bool guardar(Proyecto registro);
    Proyecto leer(int pos);
    int leerTodos(Proyecto registros[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();
    int buscarID(int id);


private:
    std::string _nombreArchivo;
};
