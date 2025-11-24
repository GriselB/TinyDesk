#include <iostream>
#include <string>
#include "utils.h"
#include "TicketManager.h"
#include "Ticket.h"

using namespace std;

TicketManager::TicketManager(){
}

void TicketManager::mostrarTicket(Ticket ticket) {

    cout << "========================================\n";
    cout << " TICKET N° " << ticket.getIdTicket() << "\n";
    cout << "----------------------------------------\n";
    cout << " Proyecto : " << ticket.getNombreProyecto()
         << " (ID " << ticket.getIdProyecto() << ")\n";
    cout << " Sprint   : " << ticket.getNombreSprint()
         << " (ID " << ticket.getIdSprint() << ")\n";
    cout << " Empleado : " << ticket.getIdEmpleado() << "\n";
    cout << " Estado   : " << estado.getNombreEstado(ticket.getStatus().getIdEstado()) << "\n";
    cout << " "; ticket.getPrioridad().mostrar();
    cout << " Detalle  : " << ticket.getDescripcionTarea() << "\n";
    cout << "========================================\n\n";
}


void TicketManager::crearTicket() {

    Ticket t;
    Sprint spr;
    Usuario u;
    UsuarioManager userManager;

    int idEmpleado = 0, pos = 0;
    char opcion;
    string descripcion;

    clear();
    cout << "========================================\n";
    cout << "         ALTA DE NUEVO TICKET           \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(1, t, pos);

    int nuevoId = _repo.getNuevoIdTicket(t.getIdProyecto(), t.getIdSprint());
    t.setIdTicket(nuevoId);

    int posSprint = _repoSprint.buscarID(t.getIdSprint(), t.getIdProyecto());
    spr = _repoSprint.leer(posSprint);

    t.setNombreSprint(spr.getNombre());

    cout << "Descripcion: ";
    cin.ignore();
    getline(cin, descripcion);

    t.setDescripcionTarea(descripcion);

    int nUsuarios = _repoUsuario.getCantidadRegistros();
    int idAreaSprint = spr.getArea().getIdArea();

    bool idEmpleadoValido = false;

    while (!idEmpleadoValido) {
        clear();
        cout << "========================================\n";
        cout << "   SELECCION DE EMPLEADO PARA EL TICKET  \n";
        cout << "========================================\n\n";

        cout << "Usuarios habilitados en el area del sprint:\n\n";

        for (int i = 0; i < nUsuarios; i++) {
            u = _repoUsuario.leer(i);

            if (userManager.verificarUsuarioArea(u.getIdUsuario(), idAreaSprint)) {
                userManager.mostrarUsuario(u);
                cout << "----------------------------------------\n";
            }
        }

        cout << "\nIngrese el ID del empleado asignado: ";
        cin >> idEmpleado;

        if (userManager.verificarUsuarioArea(idEmpleado, idAreaSprint)) {
            idEmpleadoValido = true;
        } else {
            cout << "\nEl ID ingresado no pertenece al area del sprint.\n";
            cout << "Intente nuevamente.\n";
            pause();
        }
    }

    t.setIdEmpleado(idEmpleado);

    clear();
    cout << "========================================\n";
    cout << "      SELECCION DE PRIORIDAD           \n";
    cout << "========================================\n\n";

    prioridad.seleccionarPrioridad();
    t.setPrioridad(prioridad);

    Fecha fDesdeTicket, fHastaTicket;
    bool fechasCorrectas = false;

    do {
        clear();
        cout << "========================================\n";
        cout << "        FECHAS DEL TICKET              \n";
        cout << "========================================\n\n";

        fDesdeTicket = Fecha("fecha de inicio del ticket");
        cout << "----------------------------------------\n";
        fHastaTicket = Fecha("fecha de cierre del ticket");

        string mensajeError = "";

        if (!fechaMenorOIgual(fDesdeTicket, fHastaTicket)) {
            mensajeError = "Rango invalido: la fecha de inicio no puede ser posterior a la fecha de fin del ticket.";
        }
        else if (!fechaMenorOIgual(spr.getFechaInicio(), fDesdeTicket)) {
            mensajeError = "El ticket comienza antes de la fecha de inicio del sprint ("
                         + spr.getFechaInicio().toString() + ").";
        }
        else if (!fechaMenorOIgual(fHastaTicket, spr.getFechaFin())) {
            mensajeError = "La fecha de cierre del ticket supera la fecha de fin del sprint ("
                         + spr.getFechaFin().toString() + ").";
        }

        if (mensajeError != "") {
            cout << "\n" << mensajeError << "\n";
            cout << "Por favor, vuelva a ingresar las fechas.\n";
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
    cout << "========================================\n";
    cout << "         RESUMEN DEL TICKET            \n";
    cout << "========================================\n\n";
    mostrarTicket(t);

    cout << "Confirmar creacion del ticket (S/N): ";
    cin >> opcion;

    if (toupper(opcion) == 'S') {
        if (_repo.guardarNuevo(t)) {
            clear();
            cout << "El ticket se creo correctamente.\n";
        } else {
            clear();
            cout << "Ocurrio un error al guardar el ticket.\n";
            pause();
        }
    } else {
        cout << "\nOperacion cancelada por el usuario.\n";
        pause();
    }
}


void TicketManager::bajaTicket() {
    Ticket t;

    cout << "========================================\n";
    cout << "           BAJA DE TICKET              \n";
    cout << "========================================\n\n";

    if (_repo.darDeBaja(t.getIdTicket(), t.getIdProyecto(), t.getIdSprint()))
        cout << "El ticket fue dado de baja correctamente.\n";
    else
        cout << "No se pudo realizar la baja del ticket.\n";
}


void TicketManager::reactivarTicket() {
    Ticket t;
    int pos;

    clear();
    cout << "========================================\n";
    cout << "          REACTIVAR TICKET             \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(0, t, pos);

    if (t.getStatus().getIdEstado() == 1) {
        cout << "El ticket ya se encuentra activo.\n";
        return;
    }

    estado.setIdEstado(1);
    t.setStatus(estado);

    if (_repo.guardar(pos, t))
        cout << "El ticket fue reactivado correctamente.\n";
    else
        cout << "No se pudo reactivar el ticket.\n";
}


bool TicketManager::finalizarTicketUsuario(int idUsuario){
    Ticket t;
    int pos;

    clear();
    cout << "========================================\n";
    cout << "          FINALIZAR TICKET             \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(0, t, pos);

    if (t.getStatus().getIdEstado() == 2) {
        cout << "El ticket se encuentra inactivo.\n\n";
        return false;
    }

    if (t.getIdEmpleado() != idUsuario) {
        cout << "No es posible finalizar un ticket asignado a otro usuario.\n\n";
        return false;
    }

    if (t.getFechaFinalizada().getAnio()!=0) {
        cout << "Este ticket ya fue finalizado anteriormente.\n\n";
        return false;
    }

    cout << "--- Detalle del ticket seleccionado ---\n";
    mostrarTicket(t);

    char opc;
    cout << "¿Desea finalizar este ticket? (S/N): ";
    cin >> opc;

    if (opc != 'S' && opc != 's') {
        cout << "Accion cancelada por el usuario.\n\n";
        return false;
    }

    Fecha fecha("TICKET");

    estado.setIdEstado(2);
    t.setStatus(estado);
    t.setFechaFinalizada(fecha);

    if (_repo.guardar(pos, t)) {
        cout << "El ticket se finalizo correctamente.\n\n";
        return true;
    }

    cout << "Ocurrio un error al guardar los cambios del ticket.\n";
    return false;
}


void TicketManager::modificarDescripcion() {
    Ticket t;
    int pos;

    clear();
    cout << "========================================\n";
    cout << "        MODIFICAR DESCRIPCION          \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(0, t, pos);

    string desc;
    cin.ignore();
    cout << "Descripcion actual: " << t.getDescripcionTarea() << "\n";
    cout << "Nueva descripcion: ";
    cin >> desc;

    t.setDescripcionTarea(desc);

    if (_repo.guardar(pos, t))
        cout << "La descripcion se actualizo correctamente.\n";
    else
        cout << "No se pudo actualizar la descripcion.\n";
}

void TicketManager::modificarPrioridad() {
    Ticket t;
    int pos;

    clear();
    cout << "========================================\n";
    cout << "         MODIFICAR PRIORIDAD           \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(0, t, pos);

    cin.ignore();
    cout << "Prioridad actual:\n";
    t.getPrioridad().mostrar();

    cout << "\nSeleccione la nueva prioridad:\n";
    prioridad.seleccionarPrioridad();
    t.setPrioridad(prioridad);

    if (_repo.guardar(pos, t))
        cout << "La prioridad se actualizo correctamente.\n";
    else
        cout << "No se pudo actualizar la prioridad.\n";
}


void TicketManager::modificarStatus() {
    Ticket t;
    Estado e;
    int st, pos;

    clear();
    cout << "========================================\n";
    cout << "          MODIFICAR ESTADO             \n";
    cout << "========================================\n\n";

    cargarProyectoSprint(0, t, pos);

    cout << "Estado actual: " << e.getNombreEstado(t.getStatus().getIdEstado()) << "\n";
    cout << "Ingrese el nuevo estado (0, 1 o 2): ";
    estado.seleccionarEstado();
    t.setStatus(estado);

    if (_repo.guardar(pos, t))
        cout << "El estado se actualizo correctamente.\n";
    else
        cout << "No se pudo actualizar el estado.\n";
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
        cout << "No hay tickets cargados en el sistema.\n";
        return;
    }

    cout << "\n========================================\n";
    cout << "           LISTADO DE TICKETS          \n";
    cout << "========================================\n";

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
        cout << "No se encontraron tickets para el proyecto y sprint indicados.\n";
    }

    pause();
}


void TicketManager::cargarProyectoSprint(bool nuevo, Ticket &t, int &pos){
    int idProyecto = -1, idSprint, idTicket = -1;

    ProyectoManager proyectoManager;
    Proyecto pro;
    SprintManager sprintManager;

    while (proyectoManager.buscarIDyAlta(idProyecto) == -1){
        clear();
        cout << "========================================\n";
        cout << "        SELECCION DE PROYECTO          \n";
        cout << "========================================\n\n";

        proyectoManager.listarProyectosNombreID();
        cout << "\nIngrese el ID del proyecto (0 para salir): ";
        cin >> idProyecto;

        int posProyecto = proyectoManager.buscarIDyAlta(idProyecto);
        if (idProyecto == 0) {
            clear();
            cout << "Operacion cancelada.\n";
            pause();
            return;
        }
        if (posProyecto == -1){
            clear();
            cout << "El ID ingresado no corresponde a un proyecto activo.\n";
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
        cout << "========================================\n";
        cout << "          SELECCION DE SPRINT          \n";
        cout << "========================================\n\n";

        sprintManager.listarSprintsPorIDProyectos(idProyecto);
        cout << "\nIngrese el ID del sprint (0 para salir): ";
        cin >> idSprint;

        if (idSprint == 0) {
            clear();
            cout << "Operacion cancelada.\n";
            pause();
            return;
        }

        if (!sprintManager.ExisteSprint(idSprint, idProyecto) ||
            !sprintManager.SprintEstaActivo(idSprint, idProyecto)){
            clear();
            cout << "El ID ingresado no corresponde a un sprint valido o activo.\n";
            pause();
        }
    }

    t.setIdSprint(idSprint);
    clear();

    if (!nuevo){
        while(idTicket == -1){

            listarTickets(idProyecto, idSprint);

            cout << "\nIngrese el ID del ticket (0 para salir): ";
            cin >> idTicket;

            if (idTicket == 0) {
                clear();
                cout << "Operacion cancelada.\n";
                pause();
                return;
            }

            pos = _repo.buscarIDTicketSprintProyecto(idTicket, idProyecto, idSprint);
            if (pos == -1){
                clear();
                cout << "El ID ingresado no corresponde a un ticket existente.\n";
                pause();
            }
        }

        _repo.leer(pos, t);
    }
}


bool TicketManager::cancelarOperacion (int opcion){
    if (opcion == 0) {
        clear();
        cout << "Operacion cancelada por el usuario.\n";
        pause();
        return false;
    }
    return true;
}


