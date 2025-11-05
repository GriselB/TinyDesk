#pragma once
#include <string>
#include "Estado.h"

class EstadoArchivo
{
public:
    EstadoArchivo();
    EstadoArchivo(std::string nombreArchivo);
    bool guardar(Estado registro);
    Estado leer(int pos);
    int getCantidadRegistros();
    int leerTodos(Estado registros[], int cantidad);
private:
    std::string _nombreArchivo;
};

