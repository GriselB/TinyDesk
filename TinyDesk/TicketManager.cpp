#include <iostream>
#include <string>
#include "utils.h"
#include "TicketManager.h"
#include "Ticket.h"

using namespace std;

TicketManager::TicketManager(){
}

void TicketManager::mostrarTicket(Ticket ticket) {

    cout << "Ticket " << ticket.getIdTicket() << endl;
    cout << "Proyecto: " << ticket.getNombreProyecto()
         << " (ID " << ticket.getIdProyecto() << ")" << endl;
    cout << "Sprint  : " << ticket.getNombreSprint()
         << " (ID " << ticket.getIdSprint() << ")" << endl;
    cout << "Empleado: " << ticket.getIdEmpleado() << endl;
    cout << "Prioridad: " << ticket.getPrioridad().getDescripcionPrioridad(ticket.getPrioridad().getIdPrioridad()) << endl;
    cout << "Fecha inicio     : " << ticket.getFechaInicio().toString() << endl;
    cout << "Fecha a finalizar: " << ticket.getFechaFin().toString() << endl;

    if (ticket.getStatus().getIdEstado() == 2) {
        cout << "Fecha finalizacion: " << ticket.getFechaFinalizada().toString() << endl;
    } else {
        cout << "Estado           : " << estado.getNombreEstado(ticket.getStatus().getIdEstado()) << endl;
    }

    cout << "Descripcion: " << ticket.getDescripcionTarea() << endl;
    cout << "--------------------------------" << endl << endl;
}


void TicketManager::crearTicket() {

    Ticket t;
    Sprint spr;
    Usuario u;
    UsuarioManager userManager;

    int idEmpleado = 0, pos = -1;
    char opcion;
    string descripcion;

    clear();
    cout << "---- CREAR NUEVO TICKET ----" << endl << endl;

    cargarProyectoSprint(true, t, pos);
    if (pos == -1) {
        return;
    }

    int nuevoId = _repo.getNuevoIdTicket(t.getIdProyecto(), t.getIdSprint());
    t.setIdTicket(nuevoId);

    int posSprint = _repoSprint.buscarID(t.getIdSprint(), t.getIdProyecto());
    if (posSprint == -1) {
        cout << "No se encontro el sprint asociado al ticket.\n";
        pause();
        return;
    }
    spr = _repoSprint.leer(posSprint);

    t.setNombreSprint(spr.getNombre());

    cout << "Proyecto: " << t.getNombreProyecto() << " (ID " << t.getIdProyecto() << ")" << endl;
    cout << "Sprint  : " << spr.getNombre() << " (ID " << spr.getIdSprint() << ")" << endl;
    cout << "--------------------------------" << endl;

    cout << "Descripcion: ";
    cin.ignore();
    getline(cin, descripcion);

    t.setDescripcionTarea(descripcion);

    int nUsuarios = _repoUsuario.getCantidadRegistros();
    int idAreaSprint = spr.getArea().getIdArea();

    bool idEmpleadoValido = false;

    while (!idEmpleadoValido) {
        clear();
        cout << "---- SELECCION DE EMPLEADO PARA EL TICKET ----" << endl << endl;

        cout << "Usuarios habilitados en el area del sprint:" << endl << endl;

        for (int i = 0; i < nUsuarios; i++) {
            u = _repoUsuario.leer(i);

            if (userManager.verificarUsuarioArea(u.getIdUsuario(), idAreaSprint)) {
                userManager.mostrarUsuario(u);
                cout << "--------------------------------" << endl;
            }
        }

        cout << endl << "Ingrese el ID del empleado asignado: ";
        cin >> idEmpleado;

        if (userManager.verificarUsuarioArea(idEmpleado, idAreaSprint)) {
            idEmpleadoValido = true;
        } else {
            cout << endl << "El ID ingresado no pertenece al area del sprint." << endl;
            cout << "Intente nuevamente." << endl;
            pause();
        }
    }

    t.setIdEmpleado(idEmpleado);

    clear();
    cout << "---- SELECCION DE PRIORIDAD ----" << endl << endl;

    prioridad.seleccionarPrioridad();
    t.setPrioridad(prioridad);

    Fecha fDesdeTicket, fHastaTicket;
    bool fechasCorrectas = false;

    do {
        clear();
        cout << "---- FECHAS DEL TICKET ----" << endl << endl;
        cout << "Rango valido para este ticket: " << spr.getFechaInicio().toString() << " a " << spr.getFechaFin().toString() << endl;
        cout << "--------------------------------" << endl;

        fDesdeTicket = Fecha("Fecha de inicio del ticket");
        cout << "--------------------------------" << endl;
        fHastaTicket = Fecha("Fecha de cierre del ticket");

        string mensajeError = "";

        if (!fechaMenorOIgual(fDesdeTicket, fHastaTicket)) {
            mensajeError = "Rango invalido: la fecha de inicio no puede ser posterior a la fecha de fin del ticket.";
        }
        else if (!fechaMenorOIgual(spr.getFechaInicio(), fDesdeTicket)) {
            mensajeError = "El ticket comienza antes de la fecha de inicio del sprint (" + spr.getFechaInicio().toString() + ").";
        }
        else if (!fechaMenorOIgual(fHastaTicket, spr.getFechaFin())) {
            mensajeError = "La fecha de cierre del ticket supera la fecha de fin del sprint (" + spr.getFechaFin().toString() + ").";
        }

        if (mensajeError != "") {
            cout << endl << mensajeError << endl;
            cout << "Por favor, vuelva a ingresar las fechas." << endl;
            pause();
        } else {
            fechasCorrectas = true;
        }

    } while (!fechasCorrectas);

    t.setFechaInicio(fDesdeTicket);
    t.setFechaFin(fHastaTicket);

    estado.seleccionarEstado();
    t.setStatus(estado);

    clear();
    cout << "---- RESUMEN DEL TICKET ----" << endl << endl;
    mostrarTicket(t);

    cout << "Confirmar creacion del ticket (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardarNuevo(t)) {
            clear();
            cout << "El ticket se creo correctamente." << endl;
        } else {
            clear();
            cout << "Ocurrio un error al guardar el ticket." << endl;
            pause();
        }
    } else {
        cout << endl << "Operacion cancelada por el usuario." << endl;
        pause();
    }
}


void TicketManager::bajaTicket() {
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- BAJA DE TICKET ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) {
        return;
    }

    cout << "--- Detalle del ticket seleccionado ---" << endl;
    mostrarTicket(t);

    int estadoActual = t.getStatus().getIdEstado();

    if (estadoActual == 0) {
        cout << "El ticket ya se encuentra dado de baja (No Disponible)." << endl;
        pause();
        return;
    }

    char opcion;
    cout << "¿Confirmar baja del ticket? (S/N): ";
    cin >> opcion;

    if (toupper(opcion) != 'S') {
        cout << "Operacion cancelada por el usuario." << endl;
        pause();
        return;
    }

    estado.setIdEstado(0);
    t.setStatus(estado);

    if (_repo.guardar(pos, t)) {
        cout << "El ticket fue dado de baja correctamente." << endl;
    } else {
        cout << "No se pudo realizar la baja del ticket." << endl;
    }

    pause();
}


void TicketManager::reactivarTicket() {
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- REACTIVAR TICKET ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) {
        return;
    }

    if (t.getStatus().getIdEstado() == 1) {
        cout << "El ticket ya se encuentra activo." << endl;
        pause();
        return;
    }

    estado.setIdEstado(1);
    t.setStatus(estado);

    if (_repo.guardar(pos, t))
        cout << "El ticket fue reactivado correctamente." << endl;
    else
        cout << "No se pudo reactivar el ticket." << endl;

    pause();
}


bool TicketManager::finalizarTicketAdmin(){
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- FINALIZAR TICKET ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);

    if (pos == -1) return false;

    if (t.getStatus().getIdEstado() == 2) {
        cout << "El ticket se encuentra finalizado." << endl << endl;
        pause();
        return false;
    }

    if (t.getFechaFinalizada().getAnio() != 0) {
        cout << "Este ticket ya fue finalizado anteriormente." << endl << endl;
        pause();
        return false;
    }

    cout << "--- Detalle del ticket seleccionado ---" << endl;
    mostrarTicket(t);

    char opc;
    cout << "¿Desea finalizar este ticket? (S/N): ";
    cin >> opc;

    if (opc != 'S' && opc != 's') {
        cout << "Accion cancelada por el usuario." << endl << endl;
        pause();
        return false;
    }

    Fecha fecha("TICKET");

    estado.setIdEstado(2);
    t.setStatus(estado);
    t.setFechaFinalizada(fecha);

    if (_repo.guardar(pos, t)) {
        cout << "El ticket se finalizo correctamente." << endl << endl;
        pause();
        return true;
    }

    cout << "Ocurrio un error al guardar los cambios del ticket." << endl;
    pause();
    return false;
}


bool TicketManager::finalizarTicketUsuario(int idUsuario){
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- FINALIZAR TICKET ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) return false;

    if (t.getStatus().getIdEstado() == 2) {
        cout << "El ticket se encuentra inactivo." << endl << endl;
        pause();
        return false;
    }

    if (t.getIdEmpleado() != idUsuario) {
        cout << "No es posible finalizar un ticket asignado a otro usuario." << endl << endl;
        pause();
        return false;
    }

    if (t.getFechaFinalizada().getAnio() != 0) {
        cout << "Este ticket ya fue finalizado anteriormente." << endl << endl;
        pause();
        return false;
    }

    cout << "--- Detalle del ticket seleccionado ---" << endl;
    mostrarTicket(t);

    char opc;
    cout << "¿Desea finalizar este ticket? (S/N): ";
    cin >> opc;

    if (opc != 'S' && opc != 's') {
        cout << "Accion cancelada por el usuario." << endl << endl;
        pause();
        return false;
    }

    Fecha fecha("TICKET");

    estado.setIdEstado(2);
    t.setStatus(estado);
    t.setFechaFinalizada(fecha);

    if (_repo.guardar(pos, t)) {
        cout << "El ticket se finalizo correctamente." << endl << endl;
        pause();
        return true;
    }

    cout << "Ocurrio un error al guardar los cambios del ticket." << endl;
    pause();
    return false;
}


void TicketManager::modificarDescripcion() {
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- MODIFICAR DESCRIPCION ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) return;

    string desc;
    cin.ignore();
    cout << "Descripcion actual: " << t.getDescripcionTarea() << endl;
    cout << "Nueva descripcion: ";
    getline(cin, desc);

    t.setDescripcionTarea(desc);

    if (_repo.guardar(pos, t))
        cout << "La descripcion se actualizo correctamente." << endl;
    else
        cout << "No se pudo actualizar la descripcion." << endl;

    pause();
}


void TicketManager::modificarPrioridad() {
    Ticket t;
    int pos = -1;

    clear();
    cout << "---- MODIFICAR PRIORIDAD ----" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) return;

    cin.ignore();
    cout << "Prioridad actual:" << endl;
    t.getPrioridad().mostrar();

    cout << endl << "Seleccione la nueva prioridad:" << endl;
    prioridad.seleccionarPrioridad();
    t.setPrioridad(prioridad);

    if (_repo.guardar(pos, t))
        cout << "La prioridad se actualizo correctamente." << endl;
    else
        cout << "No se pudo actualizar la prioridad." << endl;

    pause();
}


void TicketManager::modificarStatus() {
    Ticket t;
    Estado e;
    int pos = -1;

    clear();
    cout << "---- MODIFICAR ESTADO ----" << endl << endl;
    cout << "(Funcion pensada en caso de que existiera mas de 3 estados)" << endl << endl;

    cargarProyectoSprint(false, t, pos);
    if (pos == -1) return;

    cout << "Estado actual: " << e.getNombreEstado(t.getStatus().getIdEstado()) << endl << endl;

    cout << "Seleccione el nuevo estado:" << endl;
    estado.seleccionarEstado();
    t.setStatus(estado);

    if (_repo.guardar(pos, t))
        cout << "El estado se actualizo correctamente." << endl;
    else
        cout << "No se pudo actualizar el estado." << endl;

    pause();
}


void TicketManager::listarTickets(int idProyecto, int idSprint) {

    int n = _repo.getCantidadRegistros();
    if (n == 0) {
        cout << "No hay tickets cargados en el sistema." << endl;
        return;
    }

    cout << endl;
    cout << "----- LISTADO DE TICKETS -----" << endl;

    bool hayTickets = false;

    for (int i = 0; i < n; i++) {
        Ticket r;
        bool existeTicket = _repo.leer(i, r);
        if (!existeTicket) continue;

        if ((_repo.buscarIDTicketSprintProyecto(r.getIdTicket(), idProyecto, idSprint) != -1) &&
            (r.getIdProyecto() == idProyecto && r.getIdSprint() == idSprint)) {
            hayTickets = true;
            mostrarTicket(r);
        }
    }

    if (!hayTickets) {
        cout << "No se encontraron tickets para el proyecto y sprint indicados." << endl;
    }

    pause();
}


void TicketManager::cargarProyectoSprint(bool nuevo, Ticket &t, int &pos){
    pos = -1;
    int idProyecto = -1, idSprint = -1, idTicket = -1;

    ProyectoManager proyectoManager;
    Proyecto pro;
    SprintManager sprintManager;

    while (proyectoManager.buscarIDyAlta(idProyecto) == -1){
        clear();
        cout << "---- SELECCION DE PROYECTO ----" << endl << endl;

        proyectoManager.listarProyectosNombreID();
        cout << endl << "Ingrese el ID del proyecto (0 para salir): ";
        cin >> idProyecto;

        int posProyecto = proyectoManager.buscarIDyAlta(idProyecto);
        if (idProyecto == 0) {
            clear();
            cout << "Operacion cancelada." << endl;
            pause();
            pos = -1;
            return;
        }
        if (posProyecto == -1){
            clear();
            cout << "El ID ingresado no corresponde a un proyecto activo." << endl;
            pause();
        } else {
            pos = posProyecto;
        }
    }

    pro = _repoProyecto.leer(pos);

    t.setIdProyecto(idProyecto);
    t.setNombreProyecto(pro.getNombre());

    while(!sprintManager.ExisteSprint(idSprint, idProyecto)){
        clear();
        cout << "---- SELECCION DE SPRINT ----" << endl << endl;

        sprintManager.listarSprintsPorIDProyectos(idProyecto);
        cout << endl << "Ingrese el ID del sprint (0 para salir): ";
        cin >> idSprint;

        if (idSprint == 0) {
            clear();
            cout << "Operacion cancelada." << endl;
            pause();
            pos = -1;
            return;
        }

        if (!sprintManager.ExisteSprint(idSprint, idProyecto) || !sprintManager.SprintEstaActivo(idSprint, idProyecto)){
            clear();
            cout << "El ID ingresado no corresponde a un sprint valido o activo." << endl;
            pause();
        }
    }

    t.setIdSprint(idSprint);
    clear();

    if (!nuevo){
        while(idTicket == -1){

            listarTickets(idProyecto, idSprint);

            cout << endl << "Ingrese el ID del ticket (0 para salir): ";
            cin >> idTicket;

            if (idTicket == 0) {
                clear();
                cout << "Operacion cancelada." << endl;
                pause();
                pos = -1;
                return;
            }

            pos = _repo.buscarIDTicketSprintProyecto(idTicket, idProyecto, idSprint);
            if (pos == -1){
                clear();
                cout << "El ID ingresado no corresponde a un ticket existente." << endl;
                pause();
            }
        }

        _repo.leer(pos, t);
    }
}
