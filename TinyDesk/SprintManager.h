#pragma once
#include <string>
#include "Sprint.h"
#include "SprintArchivo.h"

class SprintManager {
private:
    SprintArchivo _repo;
    
protected:
    void Mostrar(Sprint sprint);

public:
    SprintManager();
    
    void Cargar();
    void generarNombre();
    void cargarFecha(Fecha &f, const std::string nombre);
    void crearSprint();
    void listarSprints();
    void mostrarSprintPorID();
    void mostrar(int pos, bool activo);
    void finalizarSprint();
    void eliminarSprintLogico();  // Cambia activo => false
};
