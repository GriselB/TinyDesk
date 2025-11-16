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
#include "Estado.h"

using namespace std;

SprintManager::SprintManager() { }

//----------------------------------------------
void SprintManager::crearSprint() {
    cout << "---- CREAR NUEVO SPRINT ----" << endl;
    int idProyecto = seleccionarProyecto(); 

    if (idProyecto == 0) {
        cout << "No se seleccionó ningún proyecto. Cancelando creación." << endl;
        return;
    }

    Cargar(idProyecto);
}
//----------------------------------------------

int SprintManager::seleccionarProyecto() {
    ProyectoManager proyecto;
    cout << "A continuacion se mostrara la lista de proyectos para asignar el Sprint"<< endl;
    proyecto.listarProyectosNombreID();

    int idProyecto;
    cout << "Ingrese el ID del proyecto al que pertenece el sprint (0 para cancelar): ";
    cin >> idProyecto;
    clear();
    return idProyecto;
}


//-------------------------------------------
void SprintManager::Cargar(int idProyecto) {
    int idSprint;
    string nombreSprint;
    bool activo = true;
    char opcion;

    Sprint sprint;
    Area area;
    Estado estado;
    
//    int cantidadExistente = _repo.contarPorProyecto(idProyecto);
//    _contadorSprint = cantidadExistente + 1;
//    _ultimoProyectoID = idProyecto;

    idSprint = _repo.getNuevoID(idProyecto);
    sprint.setIdSprint(idSprint);

    cout << "\n=== CARGA DE NUEVO SPRINT ===" << endl;
    cout << "Sprint #" << idSprint << endl;

    sprint.setFechaInicio();
    sprint.setFechaFin();

    nombreSprint = "Sprint " + to_string(idSprint)+" ("+sprint.getFechaInicio()+" - "+sprint.getFechaFin()+")";
    sprint.setNombre(nombreSprint);


    area.seleccionar(); 
    sprint.setArea(area);
    
    sprint.setIdProyecto(idProyecto);
    sprint.setIdEstado(1);

    // Mostrar resumen antes de guardar
    cout << "\n=== RESUMEN DEL SPRINT CARGADO ===" << endl;
    /*cout << "Nombre: " << sprint.getNombre() << endl;
    cout << "Proyecto ID: " << sprint.getIdProyecto() << endl;
    cout << "Área ID: " << sprint.getArea().getNombreArea() << endl;
    cout << "Inicio: " << sprint.getFechaInicio()<< endl;
    cout << "Fin: " << sprint.getFechaFin() << endl;
    cout << "Estado: " << estado.getNombreEstado(getIdEstado()-1)<< endl;*/
    Mostrar(sprint);
    cout << "===================================" << endl;


    cout << "\n¿Desea guardar este sprint? (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardar(sprint)) {
            cout << "\nSprint guardado exitosamente." << endl;
            pause();
        } else {
            cout << "\nError al guardar el sprint." << endl;
            pause();
        }
    } else {
        cout << "\nOperación cancelada. No se guardó el sprint." << endl;
        pause();
    }
}

//----------------------------------------------

//----------------------------------------------

void SprintManager::Mostrar(Sprint sprint) {
    Estado estado;
    //cout << "Sprint: " << sprint.getIdSprint() << endl;
    cout <<  sprint.getNombre() << endl;
    cout << "Proyecto ID: " << sprint.getIdProyecto() << endl;
    cout << "Área ID: " << sprint.getArea().getNombreArea() << endl;
    cout << "Fecha Inicio: " << sprint.getFechaInicio() << endl;
    cout << "Fecha Fin: " << sprint.getFechaFin() << endl;
    cout << "Estado: " << estado.getNombreEstado(sprint.getIdEstado()) << endl;
    if(sprint.getIdEstado()==2)
        cout<<"Fecha de finalizacion del sprint: "<<sprint.getFechaFinalizada()<<endl;
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
    int id_proyecto, id_sprint, pos;
    Sprint sprint;
    char finalizado;
    ProyectoManager proyecto;

    cout << "---- FINALIZAR SPRINT ----" << endl;
    cout << "                         " << endl;
    cout << "---- SELECCIONA UN PROYECTO ----" << endl;
    
    proyecto.listarProyectosNombreID();
    
    cout << "Ingrese el ID del proyecto: ";
    cin >> id_proyecto;
    
    listarSprintsPorIDProyectos(id_proyecto);
    
    cout << "Ingrese el ID del Sprint a finalizar: ";
    cin >> id_sprint;

    pos = _repo.buscarID(id_sprint, id_proyecto);
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
        sprint.setIdEstado(2);

        if (_repo.guardar(pos, sprint)) {
            cout << "El Sprint fue finalizado correctamente." << endl;
            pause();
        } else {
            cout << "Ocurrió un error al finalizar el Sprint." << endl;
            pause();
        }
    }

    pause();
}

//----------------------------------------------

void SprintManager::eliminarSprintLogico() {
    int id_sprint, id_proyecto, pos;
    Sprint sprint;
    char eliminado;
    ProyectoManager proyecto;

    cout << "---- ELIMINAR SPRINT ----" << endl;
    cout << "                         " << endl;
    cout << "---- SELECCIONA UN PROYECTO ----" << endl;
    
    proyecto.listarProyectosNombreID();
    
    cout << "Ingrese el ID del proyecto: ";
    cin >> id_proyecto;
    
    listarSprintsPorIDProyectos(id_proyecto);
    
    cout << "Ingrese el ID del Sprint a Eliminar: ";
    cin >> id_sprint;

    pos = _repo.buscarID(id_sprint, id_proyecto);
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        pause();
        return;
    }

    cout << "¿Confirma eliminar el Sprint? (s/n): ";
    cin >> eliminado;

    if (eliminado == 's' || eliminado == 'S') {
        if (_repo.eliminar(pos)) {
            cout << "El Sprint fue eliminado correctamente." << endl;
            pause();
        } else {
            cout << "Ocurrió un error en la eliminación del Sprint." << endl;
            pause();
        }
    }

    pause();
}

//--------------------------------------------------------------

void SprintManager::listarSprintsPorIDProyectos(int idProyecto) {
   clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    SprintManager sprintMng;
    Proyecto proyecto;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();

    cout << "                       ----- SPRINTS POR PROYECTO -----" << endl;
    cout << endl;

    if (cantProyectos <= 0) {
        cout << "No hay proyectos registrados." << endl;
        pause();
        return;
    }

    if (cantSprints <= 0) {
        cout << "No hay sprints registrados." << endl;
        pause();
        return;
    }


    bool encontrado = false;

    for (int i = 0; i < cantProyectos; i++) {
        proyecto = archivoProyecto.leer(i);
        if (proyecto.getIdProyecto() == idProyecto) {
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "No se encontró un proyecto con el ID " << idProyecto << "." << endl;
        pause();
        return;
    }

    cout << "Proyecto: " << proyecto.getNombre() 
         << " (ID: " << proyecto.getIdProyecto() << ")" << endl;
    cout << "--------------------------------------" << endl;

    bool tieneSprint = false;

    for (int j = 0; j < cantSprints; j++) {
        Sprint sprint = archivoSprint.leer(j);

        if (sprint.getIdProyecto() == idProyecto) {
            sprintMng.mostrar(j, true);
            cout << "--------------------------------------" << endl;
            tieneSprint = true;
        }
    }

    if (!tieneSprint) {
        cout << "   -- Este proyecto no tiene sprints asignados --" << endl;
    }

    //pause();
}


bool SprintManager::ExisteSprint(int idSprint, int idProyecto) {
    SprintArchivo archivoSprint;
    Sprint sprint;
    
    int cantSprints = archivoSprint.getCantidadRegistros();

    for (int j = 0; j < cantSprints; j++) {
        sprint = archivoSprint.leer(j);

        if (sprint.getIdProyecto() == idProyecto && sprint.getIdSprint() == idSprint) {
            return true;  
        }
    }

    return false;  
}

bool SprintManager::SprintEstaActivo(int idSprint, int idProyecto) {
    SprintArchivo archivoSprint;
    Sprint sprint;
    
    int cantSprints = archivoSprint.getCantidadRegistros();

    for (int i = 0; i < cantSprints; i++) {
        sprint = archivoSprint.leer(i);

        if (sprint.getIdSprint() == idSprint && sprint.getIdProyecto() == idProyecto) {
            
            return (sprint.getIdEstado() == 1);
        }
    }

    return false; 
}
