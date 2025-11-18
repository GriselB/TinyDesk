#pragma once
#include <string>
#include "Ticket.h"
#include "TicketArchivo.h"
#include "ProyectoManager.h"
#include "SprintManager.h"
#include "ProyectoArchivo.h"

class TicketManager
{
public:
    TicketManager();

    void mostrarTicket(Ticket ticket);
    void crearTicket();
    void bajaTicket();
    void reactivarTicket();

    void modificarDescripcion();
    void modificarPrioridad();
    void modificarStatus();
    //void asignarNuevoEmpleado();
    void listarTicketsPorProyectoSprint(int idProyecto, int idSprint);
    void listarTodosLosTickets();
    void listarTickets(int idProyecto, int idSprint);
    void cargarProyectoSprint(bool nuevo, Ticket &ticket);

    bool finalizarTicketUsuario(int idUsuario);

private:
    TicketArchivo _repo;
    ProyectoManager proyectoManager;
    SprintManager sprintManager;
    Proyecto p;
    Fecha f;
    Estado estado;

    ProyectoArchivo _proyectoA;

};
