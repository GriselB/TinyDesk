#pragma once
#include <string>
#include "Sprint.h"

class SprintArchivo
{
  public:
    SprintArchivo(std::string nombreArchivo = "sprints.dat");

    bool guardar(Sprint registro);
    bool guardar(int pos, Sprint registro);
    int  buscarID(int idSprint, int idProyecto);
    bool eliminar(int pos);
    int contarPorProyecto(int idProyecto);
    
    Sprint leer(int pos);
    int leerTodos(Sprint registros[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID(int idProyecto);

  private:
    std::string _nombreArchivo;
};

