#include <iostream>
#include <string>
#include "utils.h"
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
         << " | Descripcion: " << ticket.getDescripcionTarea() << "\n"
         << "======================== \n";
}

void TicketManager::crearTicket() {
    Ticket t;
    Proyecto pro;
    Sprint spr;

    string prioridad, descripcion;
    char opcion;
    int idEmpleado;

    clear();
    cout << "=== Nuevo ticket ===\n\n";



    int nuevoId = _repo.getNuevoIdTicket(t.getIdProyecto(), t.getIdSprint());
    t.setIdTicket(nuevoId);

    cout << "ID de empleado asignado: ";
    cin >> idEmpleado;
    t.setIdEmpleado(idEmpleado);
    clear();

    cout << "Prioridad (1=Baja, 2=Media, 3=Alta): ";
    cin >> prioridad;
    t.setPrioridad(prioridad);

    cout << "Descripcion: ";
    cin >> descripcion;
    t.setDescripcionTarea(descripcion);

    t.setStatus(1);

    clear();
    cout << "Resumen del ticket:\n\n";
    mostrarTicket(t);

    cout << "\nConfirmar ticket (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardarNuevo(t)) {
            clear();
            cout << "Ticket creado correctamente.\n";
        } else {
            clear();
            cout << "Error al crear el ticket.\n";
            pause();
        }
    } else {
        cout << "\nOperacion cancelada.\n";
        pause();
    }
}

void TicketManager::bajaTicket() {
    Ticket t;
    int pos;

    cargarProyectoSprint(0, t, pos);
    t.setStatus(0);

    if (_repo.guardar(pos, t)) cout << "Ticket dado de baja exitosamente.\n";
    else cout << "No se pudo dar de baja el ticket.\n";
    pause();
}

void TicketManager::reactivarTicket() {
Ticket t;
int pos;

    cargarProyectoSprint(0, t, pos);
    if (t.getStatus() == 1) { cout << "El ticket ya está activo.\n"; return; }

    t.setStatus(1);

    if (_repo.guardar(pos, t)) cout << "Ticket reactivado.\n";
    else cout << "No se pudo reactivar el ticket.\n";
    pause();
}

bool TicketManager::finalizarTicketUsuario(int idUsuario){
Ticket t;
int pos;

    cargarProyectoSprint(0, t, pos);

    if (t.getStatus() == 2) {
        cout << "El ticket esta inactivo.\n" << endl;
        return false;
    }

    if (t.getIdEmpleado() != idUsuario) {
        cout << "No puede finalizar un ticket que no le pertenece.\n" << endl;
        return false;
    }

    if (t.getFechaFinalizada().getAnio()!=0) {
        cout << "Este ticket ya fue finalizado.\n" << endl;
        return false;
    }

    cout << "--- TICKET:";
    mostrarTicket(t);

    char opc;
    cout << "ÀFinalizar este ticket? (S/N): ";
    cin >> opc;

    if (opc != 'S' && opc != 's') {
        cout << "Accion cancelada.\n" << endl;
        return false;
    }

    Fecha fecha("TICKET");
    t.setStatus(2);
    t.setFechaFinalizada(fecha);

    if (_repo.guardar(pos, t)) {
        cout << "Ticket finalizado correctamente.\n" << endl;
        return true;
    }

    cout << "Error al guardar el ticket.\n";
    return false;
}

void TicketManager::modificarDescripcion() {
Ticket t;
int pos;

    cargarProyectoSprint(0, t, pos);

    string desc;
    cin.ignore();
    cout << "DESCRIPCION ACTUAL: " << t.getDescripcionTarea() << "\n" ;
    cout << "NUEVA DESCRIPCION: ";
    cin >> desc;

    t.setDescripcionTarea(desc);
    if (_repo.guardar(pos, t)) cout << "Descripcion actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarPrioridad() {
Ticket t;
int pos;

    cargarProyectoSprint(0, t, pos);

    string prio;
    cin.ignore();
    cout << "PRIORIDAD ACTUAL" << t.getPrioridad() << "\n" ;
    cout << "ESTABLECER NUEVA PRIORIDAD: ";
    cin >> prio;
    t.setPrioridad(prio);

    if (_repo.guardar(pos, t)) cout << "Prioridad actualizada.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::modificarStatus() {
Ticket t;
int st, pos;

    cargarProyectoSprint(0, t, pos);

    cout << "ESTADO ACTUAL: " << estado.getNombreEstado(t.getStatus()) << "\n" ;
    cout << "NUEVO ESTADO: ";
    cin >> st;

    while(st < 0 || st > 2){

        cout << "NO EXISTE ESE NUMERO DE ESTADO" << "\n" ;
        cout << "NUEVO ESTADO: ";
        cin >> st;
    }

    t.setStatus(st);

    if (_repo.guardar(pos, t)) cout << "Estado actualizado.\n";
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
        if ((_repo.buscarIDTicketSprintProyecto(r.getIdTicket(), idProyecto, idSprint) != -1) && (r.getIdProyecto() == idProyecto && r.getIdSprint() == idSprint))
        mostrarTicket(r);
    }
    pause();
}

void TicketManager::cargarProyectoSprint(bool nuevo, Ticket &t, int &pos){
int idProyecto = -1, idSprint, idTicket = -1;

ProyectoManager proyectoManager;
SprintManager sprintManager;

    while (proyectoManager.buscarIDyAlta(idProyecto) == -1){
        proyectoManager.listarProyectosNombreID();
        cout << "--- Ingrese el numero de proyecto ---\n";
        cout << "Presione 0 para salir\n";
        cout << "Numero de proyecto: ";
        cin >> idProyecto;


        int pos = proyectoManager.buscarIDyAlta(idProyecto);

            if (pos == -1){
                clear();
                cout << "El numero ingresado no corresponde a un proyecto existente" << endl;
                pause();
                clear();
            }
        }

    t.setIdProyecto(idProyecto);

    while(!sprintManager.ExisteSprint(idSprint, idProyecto)){
        clear();
        sprintManager.listarSprintsPorIDProyectos(idProyecto);
        cout << "--- Seleccione el numero de sprint ---\n";
        cout << "Presione 0 para salir\n";
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

            cout << "--- Seleccione el ticket ---\n";
            cout << "Presione 0 para salir\n";
            cout << "Numero de ticket: ";
            cin >> idTicket;

            pos = _repo.buscarIDTicketSprintProyecto(idTicket, idProyecto, idSprint);
                if (pos == -1){
                    clear();
                    cout << "El numero ingresado no corresponde a un ticket existente" << endl;
                    pause();
                }
        }

    _repo.leer(pos, t);

    }
}

bool TicketManager::cancelarOperacion (int opcion){
if (opcion == 0) {
            clear();
            cout << "Operacion cancelada.\n";
            pause();
            return false;
        }
}

