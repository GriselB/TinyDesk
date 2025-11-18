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
    void listarProyectosNombreID();
    void mostrarProyectoPorId();
    void finalizarProyecto();
    void bajaLogicaProyecto();
    void altaLogicaProyecto();
    int buscarID(int id);
    int buscarIDyAlta(int id);
private:
    ProyectoArchivo _repo;
};
