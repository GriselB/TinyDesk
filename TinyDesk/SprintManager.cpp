#include <iostream>
#include "SprintManager.h"
#include "Sprint.h"

using namespace std;

SprintManager::SprintManager() { }

void SprintManager::Cargar() {

    string nombreSprint;
    int idArea, idProyecto;
    Fecha fechaInicio, fechaFin;
    Sprint sprint;

    cargarFecha(fechaInicio, "inicio");
    sprint.setFechaInicio(fechaInicio);

    cargarFecha(fechaFin, "fin");
    sprint.setFechaFin(fechaFin);

    generarNombre();

    Area area;
    area.mostrarOpciones();

    sprint.setActivo(true);
}

void SprintManager::Mostrar(Sprint sprint) {
    Proyecto proyecto;
    cout << "ID Sprint: " << sprint.getIdSprint() << endl;
    cout << "Nombre: "  << sprint.getNombre() << endl;

    cout << "Proyecto: " << proyecto.getIdProyecto() << endl;

    cout << "ID �rea: " << sprint.getIdArea() << endl;

    cout << "Fecha Inicio: " << sprint.getFechaInicio().toString() << endl;
    cout << "Fecha Fin:   " << sprint.getFechaFin().toString() << endl;

    cout << "Activo: " << (sprint.getActivo() ? "S�" : "No") << endl;
}

void SprintManager::mostrar(int pos, bool activo) {
    //Proyecto proyecto;
    SprintArchivo sprintArch;
    int cant = sprintArch.getCantidadRegistros();
    if (pos < 0 || pos >= cant) {
        cout << "Posicion de sprint invalida."<<endl;
        return;
    }
    
    Sprint sprint = sprintArch.leer(pos);
    cout << "ID Sprint: " << sprint.getIdSprint() << endl;
    cout << "Nombre: "  << sprint.getNombre() << endl;
    
    //cout << "Proyecto: " << proyecto.getIdProyecto() << endl;

    cout << "ID �rea: " << sprint.getIdArea() << endl;

    cout << "Fecha Inicio: " << sprint.getFechaInicio().toString() << endl;
    cout << "Fecha Fin:   " << sprint.getFechaFin().toString() << endl;
    if(activo){
        cout << "Activo: " << (sprint.getActivo() ? "S�" : "No") << endl;
    }
}

void SprintManager::generarNombre() {
  Proyecto proyecto;
  Sprint sprint;
    string nombre = proyecto.getNombre() + " - Sprint " + to_string(sprint.getIdSprint()) +
                    " (" + sprint.getFechaInicio().toString() + " - " +
                    sprint.getFechaFin().toString() + ")";
    sprint.setNombre(nombre);
}

void SprintManager::cargarFecha(Fecha &f, const string nombre) {
    int dia, mes, anio;
    cout << "Ingrese d�a de " << nombre << ": ";
    cin >> dia;
    cout << "Ingrese mes de " << nombre << ": ";
    cin >> mes;
    cout << "Ingrese a�o de " << nombre << ": ";
    cin >> anio;

    f.setDia(dia);
    f.setMes(mes);
    f.setAnio(anio);
}

void SprintManager::crearSprint() {

    system("cls");

    cout << "---- CREAR NUEVO SPRINT ----" << endl;
    Sprint sprint;
    Cargar();
    
    sprint.setIdSprint(_repo.getNuevoID());
    sprint.setStatus("Pendiente");  
    sprint.setActivo(true);

    
    

    if (_repo.guardar(sprint)) {
        cout << "Sprint guardado con éxito."<<endl;
        cout << "ID: " << sprint.getIdSprint() << endl;
        system("pause");
    } else {
        cout << "Error al guardar el sprint." << endl;
        system("pause");
    }
}


void SprintManager::listarSprints() {
    int cantReg = _repo.getCantidadRegistros();
    if (cantReg <= 0) {
        cout << "No hay sprints cargados." << endl;
        system("pause");
        return;
    }

    Sprint *reg = new Sprint[cantReg];
    if (reg == NULL) {
        cout << "Sin memoria." << endl;
        system("pause");
        exit(-100);
        return;
    }
  

    _repo.leerTodos(reg, cantReg);

    system("cls");
    cout<<"---- LISTA DE SPRINTS ----" << endl;
    for (int i = 0; i < cantReg; i++) {
        //reg[i] Mostrar();
        Sprint sprint = _repo.leer(i);
        Mostrar(sprint);
        cout << "--------------------------------" << endl;
    }
    system("pause");

    delete [] reg;
}


void SprintManager::mostrarSprintPorID() {
    int id;
    cout << "Ingrese ID del Sprint: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un Sprint con ese ID." << endl;
        system("pause");
        return;
    }

    Sprint sprint = _repo.leer(pos);
    Mostrar(sprint);
    system("pause");
}

void SprintManager::finalizarSprint() {
    int id, pos;
    Sprint sprint;
    char finalizado;
    
    cout << "---- FINALIZAR SPRINT ----" << endl;
    cout << "ID del Sprint a finalizar: ";
    cin >> id;

    pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un Sprint con ese ID." << endl;
        system("pause");
        return;
    }

    sprint = _repo.leer(pos);
    
    cout << "Informacion del Sprint: "<<endl;

    Mostrar(sprint);
     cout << endl << "Quiere finalizarlo S/N:";
     cin >> finalizado;

    if(finalizado== 's' || finalizado == 'S')
    {
        sprint.setStatus("Finalizado");
        sprint.setFechaFinalizada();
        cout << "El Sprint fue eliminado correctamente "<<endl;
    }
    
    if(_repo.guardar(pos, sprint))
    {
      cout << "El Sprint fue finalizado correctamente "<<endl;
    }
    else
    {
      cout << "Ocurrio un error, no pudimos finalziar el Sprint"  << endl;
    }
    
    

    system("pause");
}

void SprintManager::eliminarSprintLogico() {
    int id, pos;
    Sprint sprint;
    SprintArchivo archivoSprint;
    char eliminado;
    
    cout << "---- ELIMINAR TAREA ----" << endl;
    cout << "Ingrese ID del Sprint a desactivar: ";
    cin >> id;

    pos = _repo.buscarID(id);
    
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        system("pause");
        return;
    }

    sprint = _repo.leer(pos);
    cout << "Informacion del Sprint: "<<endl;

    Mostrar(sprint);
     cout << endl << "Quiere eliminarlo S/N:";
     cin >> eliminado;

    if(eliminado== 's' || eliminado == 'S')
    {  
      if(archivoSprint.eliminar(pos))
      {
        cout << "El Sprint fue eliminado correctamente "<<endl;
      }
      else
      {
        cout << "Ocurrio un error en la eliminacion del Sprint"  << endl;
      }
    }
    
    system("pause");
}
