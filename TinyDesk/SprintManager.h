#pragma once
#include <string>
#include "SprintArchivo.h"
#include "Sprint.h"
#include "Fecha.h"
#include "Area.h"
#include "Proyecto.h"

class SprintManager {
private:
    SprintArchivo _repo;
    int _ultimoProyectoID = -1;
    int _contadorSprint = 1;
    
    void Cargar(int idProyecto);
    int seleccionarProyecto(); 

protected:
    void Mostrar(Sprint sprint);

public:
    SprintManager();


    void ListarProyectos();
    void crearSprint();
    void listarProyectos(); 
    void listarSprints();
    void mostrar(int pos, bool activo);
    void listarSprintsPorIDProyectos(int idProyecto);
    bool ExisteSprint(int idSprint, int idProyecto);
    bool SprintEstaActivo(int idSprint, int idProyecto); 
    
    void finalizarSprint();
    void eliminarSprintLogico();  
};
