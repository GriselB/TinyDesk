#include <iostream>
#include "TicketManager.h"
#include "Ticket.h"

using namespace std;

TicketManager::TicketManager(){
}

void TicketManager::mostrarTicket(Ticket ticket) {
    cout << "ID: " << ticket.getIdTicket()
         << " | Empleado: " << ticket.getIdEmpleado()
         << " | Sprint: " << ticket.getIdSprint()
         << " | Proyecto: " << ticket.getIdProyecto()
         << " | Estado: " << ticket.getStatus()
         << " | Prioridad: " << ticket.getPrioridad()
         << " | Activo: " << (ticket.getActivo() ? "SI" : "NO")
         << "\n    Descripcion: " << ticket.getDescripcionTarea()
         << "\n";
}

void TicketManager::crearTicket() {
    Ticket t;

    //Proyecto pro;
    //Sprint spr;

    int idEmpleado, idSprint=-1, idProyecto=-1;
    string status, prioridad, descripcion;

    proyectoM.listarProyectosNombreID();
    cout << "Seleccione el id del proyecto a asignar:";
    cin >> idProyecto;

    // ¿Que manera hay de poder verificar si el numero de proyecto que ingreso existe sin acceder al repo desde el ticketManager? ¿Se puede hacer algo dentro del manager de proyecto?
    //if (idProyecto == -1){
        //clear();
        //cout << "El numero ingresado no corresponde a un proyecto existente" << endl;
        //pause();
        //clear();
        //}
    //}

    t.setIdProyecto(idProyecto);
    clear();

    //while(idSprint == -1){
    cout << "SPRINTS DISPONIBLES"<< endl;
    cout << "---------------------"<< endl;
    sprintM.listarSprints();
    //sprint. <--- funcion para listar los sprints que tengan asociados el nro de proyecto que se selecciono antes


    cout << "Seleccione el id del sprint a asignar:";
    cin >> idSprint;

    //idSprint = spr.getIdSprint(idSprint);

    // Mismo caso que arriba, que se puede hacer para verificar que existe ese sprint y ese proyecto
    //if (idSprint == -1){
        //clear();
        //cout << "El numero ingresado no corresponde a un sprint existente" << endl;
        //pause();
        //clear();
        //}
    //}
    t.setIdSprint(idSprint);
    clear();

    int nuevoId = _repo.getNuevoID(idProyecto, idSprint);
    t.setIdTicket(nuevoId);


    cout << "Seleccione el id del empleado asignado/n"<< endl;
    cin >> idEmpleado;
    t.setIdEmpleado(idEmpleado);

    cin.ignore();
    cout << "Estado: ";
    getline(cin, status);
    t.setStatus(status);
    cout << "Prioridad: ";
    getline(cin, prioridad);
    t.setPrioridad(prioridad);
    cout << "Descripcion: ";
    getline(cin, descripcion);
    t.setDescripcionTarea(descripcion);

    t.setFechaInicio();
    t.setActivo(true);

    if (_repo.guardar(t)) {
        cout << "Nuevo ticket creado: " << descripcion << "\n";
    } else {
        cout << "Error al crear el ticket.\n";
    }
}

void TicketManager::bajaTicket() {
    int id, idProyecto, idSprint;

    cout << "Ingrese el id del proyecto del que quiera listar.\n";
    cin >> idProyecto;
    // ¿Se puede crear una función desde proyectomanager que verifique si el id que se esta enviando existe?
    cout << "Ingrese el id del sprint del que quiera listar.\n";
    cin >> idSprint;
    // ¿Se puede crear una función desde sprintmanager que verifique si el id que se esta enviando existe?

    cout << "Ingrese el ID del ticket para darlo de baja: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    if (_repo.darDeBaja(pos, idProyecto, idSprint)) cout << "Ticket dado de baja logicamente.\n";
    else cout << "No se pudo dar de baja el ticket.\n";
}

void TicketManager::reactivarTicket() {
    int id;
    cout << "Ingrese ID de ticket a reactivar: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }

    if (r.getStatus() == "1") { cout << "El ticket ya está activo.\n"; return; }

    r.setStatus("2");

    if (_repo.guardar(r)) cout << "Ticket reactivado.\n";
    else cout << "No se pudo reactivar el ticket.\n";
}

void TicketManager::finalizarTicket() {
    int id;

    //listar tickets
    cout << "Ingrese ID de ticket para cerrarlo: ";
    cin >> id;

    //tiene que recibir idProyecto y idSprint

    //corregir buscarid
    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }
    if (!r.getActivo()) { cout << "El ticket está inactivo.\n"; return; }

    cin.ignore();
    string nuevoStatus;
    cout << "Estado (Presione enter para confirmar): ";
    getline(cin, nuevoStatus);
    if (nuevoStatus.empty()) nuevoStatus = "Finalizado";
    r.setStatus(nuevoStatus);

    r.setFechaFinalizada();

    if (_repo.guardar(r)) cout << "Ticket finalizado.\n";
    else cout << "Error al actualizar el ticket.\n";
}

void TicketManager::modificarDescripcion() {
    int id;
    cout << "ID de ticket: ";
    cin >> id;

    //pasar idProyecto y pasar idSprint, nuevo buscarid
    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }

    string desc;
    cin.ignore();
    cout << "Nueva descripcion: ";
    getline(cin, desc);
    r.setDescripcionTarea(desc);

    if (_repo.guardar(r)) cout << "Descripcion actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarPrioridad() {
    int id;
    cout << "ID de ticket: ";
    cin >> id;

    //pasar idProyecto y pasar idSprint, nuevo buscarid
    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID" << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }

    string prio;
    cin.ignore();
    cout << "Establecer nueva prioridad: ";
    getline(cin, prio);
    r.setPrioridad(prio);

    if (_repo.guardar(r)) cout << "Prioridad actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarStatus() {
    int id;
    cout << "ID de ticket: ";
    cin >> id;

    //pasar idProyecto y pasar idSprint, nuevo buscarid
    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos,r)) { cout << "Error al leer el ticket.\n"; return; }

    string st;
    cin.ignore();
    cout << "Nuevo estado: ";
    getline(cin, st);
    r.setStatus(st);

    if (_repo.guardar(r)) cout << "Estado actualizado.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::asignarNuevoEmpleado() {
    int id;
    cout << "ID de ticket: ";
    cin >> id;

    //pasar idProyecto y pasar idSprint, nuevo buscarid
    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos,r)) { cout << "Error al leer el ticket.\n"; return; }

    int empleado;
    cout << "Nuevo ID de empleado: ";
    cin >> empleado;
    r.setIdEmpleado(empleado);

    if (_repo.guardar(r)) cout << "Empleado reasignado.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::listarTickets() {
int idSprint, idProyecto;

    int n = _repo.getCantidadRegistros();
    if (n == 0) {
        cout << "No hay tickets creados.\n";
        return;
    }

    cout << "Ingrese el id del proyecto del que quiera listar.\n";
    cin >> idProyecto;
    // ¿Se puede crear una función desde proyectomanager que verifique si el id que se esta enviando existe?
    cout << "Ingrese el id del sprint del que quiera listar.\n";
    cin >> idSprint;
    // ¿Se puede crear una función desde sprintmanager que verifique si el id que se esta enviando existe?

    cout << "\n===== TICKETS CREADOS =====\n";

    for (int i = 0; i < n; i++) {
    Ticket r;
    bool existeTicket = _repo.leer(i, r);
        if (!existeTicket) continue;
        if ((_repo.buscarIDTicketSprintProyecto(r.getIdTicket(), idProyecto, idSprint) != -1) && r.getActivo() == true)
        mostrarTicket(r);
    }
}

