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
         << " | Estado: " << ticket.getStatus()
         << " | Prioridad: " << ticket.getPrioridad()
         << " | Activo: " << (ticket.getActivo() ? "SI" : "NO")
         << "\n    Descripcion: " << ticket.getDescripcionTarea()
         << "\n";
}

void TicketManager::crearTicket() {
    Ticket t;

    int idEmpleado, idSprint;
    string status, prioridad, descripcion;

    int nuevoId = _repo.getNuevoID();
    t.setIdTicket(nuevoId);

    cout << "Empleado asignado (ingresar ID): ";
    cin >> idEmpleado;
    t.setIdEmpleado(idEmpleado);

    cout << "Sprint asignado (ingresar ID): ";
    cin >> idSprint;
    t.setIdSprint(idSprint);

    if(_repo.yaExisteTicketEmpleadoSprint(t))
    {
      delete t;
      cout << "Ya existe un registro con el Empleado asignado a ese Sprint";
      return;
    }

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
    int id;
    cout << "Ingrese el ID del ticket para darlo de baja: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    if (_repo.eliminar(pos)) cout << "Ticket dado de baja logicamente.\n";
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

    if (r.getActivo()) { cout << "El ticket ya está activo.\n"; return; }

    r.setActivo(true);

    if (_repo.guardar(r)) cout << "Ticket reactivado.\n";
    else cout << "No se pudo reactivar el ticket.\n";
}

void TicketManager::finalizarTicket() {
    int id;
    cout << "Ingrese ID de ticket para cerrarlo: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }
    if (!r.getActivo()) { cout << "El ticket está inactivo.\n"; return; }

    cin.ignore();
    string nuevoStatus;
    cout << "Estadp (Presione enter para confirmar): ";
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

void TicketManager::cambiarSprint() {
    int id;
    cout << "ID de ticket: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) { cout << "No existe un ticket con ese ID " << id << "\n"; return; }

    Ticket r;
    if (!_repo.leer(pos, r)) { cout << "Error al leer el ticket.\n"; return; }

    int sprint;
    cout << "Nuevo ID de sprint: ";
    cin >> sprint;
    r.setIdSprint(sprint);

    if (_repo.guardar(r)) cout << "Sprint actualizado.\n";
    else cout << "No se pudo actualizar.\n";
}

void TicketManager::listarTickets() {
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
        if (!r.getActivo()) continue;
        mostrarTicket(r);
    }
}
