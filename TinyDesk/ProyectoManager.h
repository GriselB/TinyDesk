#pragma once
#include <string>
#include "Proyecto.h"
#include "ProyectoArchivo.h"

class ProyectoManager
{

public:
    ProyectoManager();
    void crearProyecto();
    void listarProyectos();
    void mostrarProyectoPorId();
    void finalizarProyecto();
    void bajaLogicaProyecto();
private:
    ProyectoArchivo _repo;
};
