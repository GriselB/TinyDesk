#include <iostream>
#include <string>
#include "SprintManager.h"
#include "SprintArchivo.h"
#include "Fecha.h"
#include "Area.h"
#include "Proyecto.h"
#include "ProyectoManager.h"
#include "Sprint.h"
#include "utils.h"

using namespace std;

SprintManager::SprintManager() { }

//----------------------------------------------
void SprintManager::crearSprint() {
    cout << "---- CREAR NUEVO SPRINT ----" << endl;
    int idProyecto = seleccionarProyecto(); 

    if (idProyecto == -1) {
        cout << "No se seleccionó ningún proyecto. Cancelando creación." << endl;
        return;
    }

    Cargar(idProyecto);
}
//----------------------------------------------

int SprintManager::seleccionarProyecto() {
    ProyectoManager proyecto;
    proyecto.listarProyectos();

    int idProyecto;
    cout << "\nIngrese el ID del proyecto al que pertenece el sprint (o -1 para cancelar): ";
    cin >> idProyecto;

    return idProyecto;
}


//-------------------------------------------
void SprintManager::Cargar(int idProyecto) {
    int idSprint;
    string nombreSprint;
    bool activo = true;
    char opcion;

    Sprint sprint;
    
    
  
    // --- Control de número de sprint por proyecto ---
    int cantidadExistente = _repo.contarPorProyecto(idProyecto);
    _contadorSprint = cantidadExistente + 1;
    _ultimoProyectoID = idProyecto;

    // Generar un nuevo ID automático
    idSprint = _repo.getNuevoID();
    sprint.setIdSprint(idSprint);

    cout << "\n=== CARGA DE NUEVO SPRINT ===" << endl;
    cout << "Sprint #" << idSprint << endl;

    // Cargar fechas usando la clase Fecha
    sprint.setFechaInicio();
    sprint.setFechaFin();

  

    // Generar nombre automático
    nombreSprint = "Sprint " + to_string(_contadorSprint)+" ("+sprint.getFechaInicio()+" - "+sprint.getFechaFin()+")";
    sprint.setNombre(nombreSprint);

    // Cargar área
    Area area;
    area.seleccionar(); 
    sprint.setIdArea(area.getIdArea());

    // Asignar proyecto y estado
    sprint.setIdProyecto(idProyecto);
    sprint.setActivo(activo);

    // Mostrar resumen antes de guardar
    cout << "\n=== RESUMEN DEL SPRINT CARGADO ===" << endl;
    cout << "Nombre: " << sprint.getNombre() << endl;
    cout << "Proyecto ID: " << sprint.getIdProyecto() << endl;
    cout << "Área ID: " << sprint.getIdArea() << endl;
    cout << "Inicio: " << sprint.getFechaInicio()<< endl;
    cout << "Fin: " << sprint.getFechaFin() << endl;
    cout << "Estado: " << (sprint.getActivo() ? "Activo" : "Inactivo") << endl;
    cout << "===================================" << endl;

    // Confirmación antes de guardar
    cout << "\n¿Desea guardar este sprint? (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardar(sprint)) {
            cout << "\nSprint guardado exitosamente." << endl;
        } else {
            cout << "\nError al guardar el sprint." << endl;
        }
    } else {
        cout << "\nOperación cancelada. No se guardó el sprint." << endl;
    }
}

//----------------------------------------------

//----------------------------------------------

void SprintManager::Mostrar(Sprint sprint) {
    cout << "ID Sprint: " << sprint.getIdSprint() << endl;
    cout << "Nombre: " << sprint.getNombre() << endl;
    cout << "Proyecto ID: " << sprint.getIdProyecto() << endl;
    cout << "Área ID: " << sprint.getIdArea() << endl;
    cout << "Fecha Inicio: "; sprint.getFechaInicio();
    cout << "Fecha Fin: "; sprint.getFechaFin();
    cout << "Activo: " << (sprint.getActivo() ? "Sí" : "No") << endl;
    cout << endl;
}

//----------------------------------------------

void SprintManager::mostrar(int pos, bool activo) {
    if (pos < 0) {
        cout << "Posición de sprint inválida." << endl;
        return;
    }

    Sprint sprint = _repo.leer(pos);
    Mostrar(sprint);
}

//----------------------------------------------


void SprintManager::listarSprints() {
    int cantReg = _repo.getCantidadRegistros();
    if (cantReg <= 0) {
        cout << "No hay sprints registrados." << endl;
        return;
    }

    Sprint *reg = new Sprint[cantReg];
    if (reg == nullptr) {
        cout << "Error de memoria." << endl;
        exit(-100);
    }

    _repo.leerTodos(reg, cantReg);

    for (int i = 0; i < cantReg; i++) {
        Mostrar(reg[i]);
    }

    delete[] reg;
}

//----------------------------------------------

void SprintManager::finalizarSprint() {
    int id, pos;
    Sprint sprint;
    char finalizado;

    cout << "---- FINALIZAR SPRINT ----" << endl;
    cout << "ID del Sprint a finalizar: ";
    cin >> id;

    pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        return;
    }

    sprint = _repo.leer(pos);

    cout << "Información del Sprint: " << endl;
    Mostrar(sprint);

    cout << "¿Desea finalizar el sprint? (s/n): ";
    cin >> finalizado;

    if (finalizado == 's' || finalizado == 'S') {
        sprint.setFechaFinalizada();
        sprint.setActivo(false);

        if (_repo.guardar(pos, sprint)) {
            cout << "El Sprint fue finalizado correctamente." << endl;
        } else {
            cout << "Ocurrió un error al finalizar el Sprint." << endl;
        }
    }

    system("pause");
}

//----------------------------------------------

void SprintManager::eliminarSprintLogico() {
    int id, pos;
    Sprint sprint;
    char eliminado;

    cout << "---- ELIMINAR SPRINT ----" << endl;
    cout << "Ingrese ID del Sprint a desactivar: ";
    cin >> id;

    pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        system("pause");
        return;
    }

    cout << "¿Confirma eliminar el Sprint? (s/n): ";
    cin >> eliminado;

    if (eliminado == 's' || eliminado == 'S') {
        if (_repo.eliminar(pos)) {
            cout << "El Sprint fue eliminado correctamente." << endl;
        } else {
            cout << "Ocurrió un error en la eliminación del Sprint." << endl;
        }
    }

    system("pause");
}
