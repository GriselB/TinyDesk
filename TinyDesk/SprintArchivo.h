#pragma once
#include <string>
#include "Sprint.h"

class SprintArchivo
{
  public:
    SprintArchivo(std::string nombreArchivo = "sprints.dat");

    bool guardar(Sprint registro);
    int  buscarID(int id);
    Sprint leer(int pos);

    int leerTodos(Sprint registros[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

  private:
    std::string _nombreArchivo;
};

