#include <iostream>
#include "TicketManager.h"
#include "Ticket.h"

using namespace std;

TicketManager::TicketManager(){
}

void TicketManager::mostrarTicket(Ticket ticket) {
    cout << "======================== \n"
         << " | ID: " << ticket.getIdTicket() << "\n"
         << " | Empleado: " << ticket.getIdEmpleado() << "\n"
         << " | Sprint: " << ticket.getIdSprint() << "\n"
         << " | Proyecto: " << ticket.getIdProyecto() << "\n"
         << " | Estado: " << estado.getNombreEstado(ticket.getStatus()) << "\n"
         << " | Prioridad: " << ticket.getPrioridad() << "\n"
         << " | Activo: " << (ticket.getStatus()) << "\n"
         << " | Descripcion: " << ticket.getDescripcionTarea() << "\n"
         << "======================== \n";
}

void TicketManager::crearTicket() {
Ticket t;
Proyecto pro;
Sprint spr;

string prioridad, descripcion, opcion;
int idEmpleado;


    clear();
    cargarProyectoSprint(1, t);
    int nuevoId = _repo.getNuevoIdTicket(t.getIdProyecto(), t.getIdSprint());
    t.setIdTicket(nuevoId);

    cout << "--- Seleccione el id del empleado asignado ---"<< endl;
    cin >> idEmpleado;
    t.setIdEmpleado(idEmpleado);
    clear();

    cout<<"--- Seleccione Prioridad ---"<<endl;
    cout<<"--- Baja, Media, Alta  ---"<<endl;
    cin >> opcion;


    cout << "--- Detalle la descripcion --- ";
    cin >> descripcion;

    t.setDescripcionTarea(descripcion);

    t.setStatus(0);

    if (_repo.guardar(t.getIdTicket(), t)) {
        clear();
        cout << "Nuevo ticket creado" << "\n";
        mostrarTicket(t);
        pause();
    } else {
        clear();
        cout << "Error al crear el ticket.\n";
        pause();
    }

}

void TicketManager::bajaTicket() {
    Ticket t;
    cargarProyectoSprint(0, t);

    if (_repo.darDeBaja(t.getIdTicket(), t.getIdProyecto(), t.getIdSprint())) cout << "Ticket dado de baja exitosamente.\n";
    else cout << "No se pudo dar de baja el ticket.\n";
}

void TicketManager::reactivarTicket() {
Ticket t;

    cargarProyectoSprint(0, t);

    if (t.getStatus() == 1) { cout << "El ticket ya está activo.\n"; return; }

    t.setStatus(2);

    if (_repo.guardar(t.getIdTicket(), t)) cout << "Ticket reactivado.\n";
    else cout << "No se pudo reactivar el ticket.\n";
}

bool TicketManager::finalizarTicketUsuario(int idUsuario){
Ticket t;

    cargarProyectoSprint(0, t);

    if (t.getStatus() == 2) {
        cout << "El ticket esta inactivo." << endl;
        return false;
    }

    if (t.getIdEmpleado() != idUsuario) {
        cout << "No puede finalizar un ticket que no le pertenece." << endl;
        return false;
    }

    if (t.getFechaFinalizada().getAnio()!=0) {
        cout << "Este ticket ya fue finalizado." << endl;
        return false;
    }

    cout << "--- TICKET:";
    mostrarTicket(t);

    char opc;
    cout << "ÀFinalizar este ticket? (S/N): ";
    cin >> opc;

    if (opc != 'S' && opc != 's') {
        cout << "Accion cancelada." << endl;
        return false;
    }

    Fecha fecha("TICKET");
    t.setStatus(2);
    t.setFechaFinalizada(fecha);

    if (_repo.guardar(t.getIdTicket(), t)) {
        cout << "Ticket finalizado correctamente." << endl;
        return true;
    }

    cout << "Error al guardar el ticket.";
    return false;
}

void TicketManager::modificarDescripcion() {
Ticket t;

    cargarProyectoSprint(0, t);

    string desc;
    cin.ignore();
    cout << "DESCRIPCION ACTUAL: " << t.getDescripcionTarea();
    cout << "NUEVA DESCRIPCION: ";
    cin >> desc;

    t.setDescripcionTarea(desc);
    if (_repo.guardar(t.getIdTicket(), t)) cout << "Descripcion actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarPrioridad() {
Ticket t;

    cargarProyectoSprint(0, t);

    string prio;
    cin.ignore();
    cout << "PRIORIDAD ACTUAL" << t.getPrioridad();
    cout << "ESTABLECER NUEVA PRIORIDAD: ";
    cin >> prio;
    t.setPrioridad(prio);

    if (_repo.guardar(t.getIdTicket(), t)) cout << "Prioridad actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarStatus() {
Ticket t;
int st;

    cargarProyectoSprint(0, t);

    cout << "ESTADO ACTUAL: " << estado.getNombreEstado(t.getStatus());
    cout << "NUEVO ESTADO: ";
    cin >> st;

    if (_repo.guardar(t.getIdTicket(), t)) cout << "Estado actualizado.\n";
    else cout << "No se pudo actualizar.\n";
}

// Funciona pero habria que hacer una funcion que valide si el usuario que ingresa pertenece al area del sprint del ticket
//void TicketManager::asignarNuevoEmpleado() {
//Ticket t;

    //cargarProyectoSprint(0, t);

    //int empleado;
    //cout << "Nuevo ID de empleado: ";
    //cin >> empleado;
    //t.setIdEmpleado(empleado);

    //if (_repo.guardar(t.getIdTicket(), t)) cout << "Empleado reasignado.\n";
    //else cout << "No se pudo actualizar.\n";
//}

void TicketManager::listarTickets(int idProyecto, int idSprint) {

    int n = _repo.getCantidadRegistros();
    if (n == 0) {
        cout << "No hay tickets creados.\n";
        return;
    }

    cout << "\n===== TICKETS CREADOS =====\n";

    for (int i = 0; i < n; i++) {
    Ticket r;
    bool existeTicket = _repo.leer(i, r);
        if (!existeTicket) continue;
        if ((_repo.buscarIDTicketSprintProyecto(r.getIdTicket(), idProyecto, idSprint) != -1) && r.getStatus() == 0 && r.getStatus() != 2)
        mostrarTicket(r);
    }
}

void TicketManager::cargarProyectoSprint(bool nuevo, Ticket &t){
int idProyecto = -1, idSprint, idTicket;

ProyectoManager proyectoManager;
SprintManager sprintManager;

    while (proyectoManager.buscarIDyAlta(idProyecto) == -1){
        proyectoManager.listarProyectosNombreID();
        cout << "--- Ingrese el numero de proyecto ---\n";
        cout << "Numero de proyecto: ";
        cin >> idProyecto;

        int pos = proyectoManager.buscarIDyAlta(idProyecto);

            if (pos == -1){
                clear();
                cout << "el numero ingresado no corresponde a un proyecto existente" << endl;
                pause();
                clear();
            }
        }

    t.setIdProyecto(idProyecto);

    while(!sprintManager.ExisteSprint(idSprint, idProyecto)){
        clear();
        sprintManager.listarSprintsPorIDProyectos(idProyecto);
        cout << "--- Seleccione el numero de sprint ---\n";
        cout << "Numero de Sprint: ";
        cin >> idSprint;

            if (!sprintManager.ExisteSprint(idSprint, idProyecto) && !sprintManager.SprintEstaActivo(idSprint, idProyecto)){
                clear();
                cout << "El numero ingresado no corresponde a un sprint existente" << endl;
                pause();
            }
    }

    t.setIdSprint(idSprint);
    clear();

    if (!nuevo){
        while(idTicket == -1){
            listarTickets(idProyecto, idSprint);
            cout << "--- Seleccione el ticket ---";
            cin >> idTicket;

            idTicket = _repo.buscarIDTicketSprintProyecto(idTicket, idProyecto, idSprint);
                if (idTicket == -1){
                    clear();
                    cout << "El numero ingresado no corresponde a un ticket existente" << endl;
                    pause();
                }
        }
    _repo.leer(idTicket, t);

    }
}

