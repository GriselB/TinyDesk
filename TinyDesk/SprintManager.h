#pragma once
#include <string>
#include "Sprint.h"
#include "SprintArchivo.h"

class SprintManager {
private:
    SprintArchivo _repo;

public:
    SprintManager();
    
    void crearSprint();
    void listarSprints();
    void mostrarSprintPorID();
    void finalizarSprint();
    void eliminarSprintLogico();  // Cambia activo => false
};
