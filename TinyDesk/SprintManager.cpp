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
    clear();
    cout << "---- CREAR NUEVO SPRINT ----" << endl;
    int idProyecto = seleccionarProyecto(); 

    if (idProyecto == 0) {
        cout << "No se selecciono ningun proyecto. Creacion cancelada." << endl;
        pause();
        return;
    }

    Cargar(idProyecto);
}
//----------------------------------------------

int SprintManager::seleccionarProyecto() {
    ProyectoManager proy;
    cout << "A continuacion se mostrara la lista de proyectos para asignar el Sprint"<< endl;
    proy.listarProyectosNombreID();

    int idProyecto;

    while (true) {
      cout << "Ingrese el ID del proyecto al que pertenece el sprint (0 para cancelar): ";
      cin >> idProyecto;

      if (idProyecto == 0) {

        return 0;
      }

      if (proy.buscarID(idProyecto) == -1) {
        cout << "El proyecto con ID " << idProyecto << " no existe. Intente nuevamente." << endl;
        continue; 
      }

 
    clear();
    return idProyecto;
  }
}


//-------------------------------------------
void SprintManager::Cargar(int idProyecto) {
    int idSprint, posProyecto;
    string nombreSprint, nombreProyecto;
    bool activo = true;
    char opcion;
    Fecha auxInicio, auxFin; 
    bool fechasValidas = false;

    Sprint sprint;
    Area area;
    Estado estado;
    ProyectoArchivo repoProy;
    ProyectoManager proyMg;
    Proyecto proy;
    
    idSprint = _repo.getNuevoID(idProyecto);
    sprint.setIdSprint(idSprint);
    

    posProyecto = proyMg.buscarID(idProyecto);
    proy = repoProy.leer(posProyecto);

    cout << "=== CARGA DE NUEVO SPRINT ===" << endl << endl;


    nombreProyecto = "Proyecto:" + proy.getNombre()+" (" + proy.getFechaInicio().toString() + " - " + proy.getFechaFin().toString() + ")";
    sprint.setProyectoDelSprint(nombreProyecto);
    cout << nombreProyecto << endl;

    cout << "Sprint #" << idSprint << endl;


    cout << "Seleccione el Area para este Sprint:" << endl;
    area.seleccionar(); 
    sprint.setArea(area);

    Fecha ultimaFechaArea = obtenerUltimaFechaFinPorArea(idProyecto, area.getIdArea());

    do {
        clear(); 
        
        cout << "=== CARGA DE NUEVO SPRINT ===" << endl;
        cout << nombreProyecto << endl; 
        cout << "Sprint #" << idSprint << endl;
        cout << "Area seleccionada: " << area.getNombreArea() << endl; 
        cout << "-----------------------------------" << endl;

        if (ultimaFechaArea.getAnio() != 0) { 

            cout << ">> INFO: El ultimo Sprint de esta area finalizo el: " 
                 << ultimaFechaArea.toString() << endl;
            cout << ">> (La nueva fecha de inicio debe ser posterior)" << endl;
        } else {

            cout << ">> INFO: Este sera el primer Sprint para " 
                 << area.getNombreArea() << "." << endl;
        }
        cout << "-----------------------------------" << endl;

        cout << "--- Ingreso de Fechas ---" << endl;
        
        auxInicio = Fecha("Inicio del Sprint"); 
        cout << "-------------------------" << endl;
        auxFin = Fecha("Fin del Sprint");

        fechasValidas = true; 

        if (!fechaMenorOIgual(auxInicio, auxFin)) {
            cout << "[ERROR] La fecha de inicio del Sprint debe ser anterior a la fecha de fin." << endl;
            pause();
            fechasValidas = false;
        }

       
        else if (!fechaMenorOIgual(proy.getFechaInicio(), auxInicio)) {
            cout << "[ERROR] El Sprint no puede iniciar antes que el Proyecto (" 
            << proy.getFechaInicio().toString() << ")." << endl;
            pause();
            fechasValidas = false;
        }
        
        else if (!fechaMenorOIgual(auxFin, proy.getFechaFin())) {
            cout << "[ERROR] El Sprint no puede terminar después que el Proyecto (" 
            << proy.getFechaFin().toString() << ")." << endl;
            pause();
            fechasValidas = false;
        }

        else if (ultimaFechaArea.getAnio() != 0 && fechaMenorOIgual(auxInicio, ultimaFechaArea)) {
          cout << "[ERROR] Ya existe un Sprint de esta area que termina el " 
               << ultimaFechaArea.toString() << ". " 
               << "El nuevo Sprint debe iniciar despues." << endl;
          pause();
          fechasValidas = false;
        }

    } while (!fechasValidas);
    
    sprint.setFechaInicio(auxInicio);
    sprint.setFechaFin(auxFin);

    nombreSprint = "Sprint " + to_string(idSprint)+" ("+sprint.getFechaInicio().toString()+" - "+sprint.getFechaFin().toString()+")";
    sprint.setNombre(nombreSprint);

    
    sprint.setIdProyecto(idProyecto);
    sprint.setIdEstado(1);
    


    clear();
    cout << "=== RESUMEN DEL SPRINT CARGADO ===" << endl;

    Mostrar(sprint);
    cout << "===================================" << endl;


    cout << "Desea guardar este sprint? (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardar(sprint)) {
            cout << "Sprint guardado exitosamente." << endl;
            pause();
        } else {
            cout << "Error al guardar el sprint." << endl;
            pause();
        }
    } else {
        cout << "Operación cancelada. No se guardó el sprint." << endl;
        pause();
    }
}

//----------------------------------------------

Fecha SprintManager::obtenerUltimaFechaFinPorArea(int idProyecto, int idArea) {
    Sprint reg;
    int count = _repo.getCantidadRegistros();
    
    Fecha maxFecha;
    
    bool haySprints = false;

    for (int i = 0; i < count; i++) {
        reg = _repo.leer(i);
        
        if (reg.getIdProyecto() == idProyecto && 
            reg.getArea().getIdArea() == idArea && 
            reg.getIdEstado() == 1) { 
            
            if (!haySprints) {
                maxFecha = reg.getFechaFin();
                haySprints = true;
            } else {
                if (fechaMenorOIgual(maxFecha, reg.getFechaFin())) {
                    maxFecha = reg.getFechaFin();
                }
            }
        }
    }
    
    return maxFecha;
}
//----------------------------------------------

//----------------------------------------------

void SprintManager::Mostrar(Sprint sprint) {
    Estado estado;
    cout <<  sprint.getNombre() << endl;
    cout << "Proyecto ID: " << sprint.getIdProyecto() << endl;
    cout <<  sprint.getProyectoDelSprint() << endl;
    cout << "Area: " << sprint.getArea().getNombreArea() << endl;
    cout << "Fecha Inicio: " << sprint.getFechaInicio().toString() << endl;
    cout << "Fecha Fin: " << sprint.getFechaFin().toString() << endl;
    cout << "Estado: " << estado.getNombreEstado(sprint.getIdEstado()) << endl;
    if(sprint.getIdEstado()==2){
      cout<<"Fecha de finalizacion del sprint: "<<sprint.getFechaFinalizada().toString()<<endl;
      cout <<"Finalizo Tarde:" << (sprint.getFinalizoTarde() ? "SI" : "NO") << endl;      
    }
    if(sprint.getIdEstado()==0){
      cout <<"Baja: SI"<< endl;      
    }

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
    int id_proyecto, id_sprint, pos,posProyecto;
    bool  fechasValidas;
    Fecha auxFin; 
    Sprint sprint;
    char finalizado;
    ProyectoManager proyecto;
    ProyectoArchivo repoProy;
    Proyecto proy;



    cout << "---- FINALIZAR SPRINT ----" << endl;
    cout << "                         " << endl;
    cout << "---- SELECCIONA UN PROYECTO ----" << endl;
    
    proyecto.listarProyectosNombreID();
    
    cout << "Ingrese el ID del proyecto: ";
    cin >> id_proyecto;
    
    posProyecto = proyecto.buscarID(id_proyecto);
    proy = repoProy.leer(posProyecto);
    listarSprintsPorIDProyectos(id_proyecto);
    
    cout << "Ingrese el ID del Sprint a finalizar: ";
    cin >> id_sprint;

    pos = _repo.buscarID(id_sprint, id_proyecto);
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        return;
    }

    sprint = _repo.leer(pos);
    
    clear();
    
    cout << "Informacion del Sprint: " << endl;
    Mostrar(sprint);

    cout << "Desea finalizar el sprint? (s/n): ";
    cin >> finalizado;

    if (finalizado == 's' || finalizado == 'S') {
    do{ 
      clear();
      
      cout << "---- FINALIZAR SPRINT ----" << endl;
      cout << "                         " << endl;
      cout << "Informacion del Sprint: " << endl;
      Mostrar(sprint);
      cout << "--- Ingreso de Fecha de finalizacion ---" << endl;
        
      auxFin = Fecha("Fin del Sprint");

      fechasValidas = true; 

      if (!fechaMenorOIgual(auxFin,sprint.getFechaFin())) {
        cout << "La fecha del Sprint va a finalizar despues de la fecha pactada" << endl;
        cout << "Desea finalizar el sprint? (s/n): ";
        cin >> finalizado;

        if (finalizado == 's' || finalizado == 'S'){
          sprint.setFinalizoTarde(true);
          fechasValidas = true;
        }else{
          fechasValidas = false;
        }
        
        pause();
 
      }

      else if (!fechaMenorOIgual(sprint.getFechaInicio(), auxFin)) {
            cout << "[ERROR] La fecha de fin del Sprint debe ser posterior a la fecha de incio." << endl;
            pause();
            fechasValidas = false;
      }
       
        
      else if (!fechaMenorOIgual(auxFin, proy.getFechaFin())) {
        cout << "[ERROR] El Sprint no puede terminar despues que el Proyecto (" 
        << proy.getFechaFin().toString() << ")." << endl;
        pause();
        fechasValidas = false;
      }


    } while (!fechasValidas);

    sprint.setFechaFinalizada(auxFin);
    sprint.setIdEstado(2);

    if (_repo.guardar(pos, sprint)) {
      cout << "El Sprint fue finalizado correctamente." << endl;
      pause();
    } 
    else {
        cout << "Ocurrió un error al finalizar el Sprint." << endl;
        pause();
      }

    pause();
  }
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

bool SprintManager::SprintEstaAtrasado(int idSprint, int idProyecto) {
    SprintArchivo archivoSprint;
    Sprint sprint;
    
    int cantSprints = archivoSprint.getCantidadRegistros();

    for (int i = 0; i < cantSprints; i++) {
        sprint = archivoSprint.leer(i);

        if (sprint.getIdSprint() == idSprint && sprint.getIdProyecto() == idProyecto && sprint.getIdEstado() == 2) {
            
            return (sprint.getFinalizoTarde() == true);
        }
    }

    return false; 
}

bool SprintManager::SprintEstaFinalizado(int idSprint, int idProyecto) {
    SprintArchivo archivoSprint;
    Sprint sprint;
    
    int cantSprints = archivoSprint.getCantidadRegistros();

    for (int i = 0; i < cantSprints; i++) {
        sprint = archivoSprint.leer(i);

        if (sprint.getIdSprint() == idSprint && sprint.getIdProyecto() == idProyecto) {
            
            return (sprint.getIdEstado() == 2);
        }
    }

    return false; 
}

string SprintManager::dibujarBarra(float porcentaje) {
    int anchoBarra = 20;
    int celdasLlenas = (porcentaje / 100.0) * anchoBarra;
    
    string barra = "[";
    for (int i = 0; i < anchoBarra; i++) {
        if (i < celdasLlenas) {
            barra += "#"; 
        } else {
            barra += "."; 
        }
    }
    barra += "]";
    return barra;
}
