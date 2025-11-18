#pragma once
#include <string>
#include "Ticket.h"
#include "TicketArchivo.h"
#include "ProyectoManager.h"
#include "SprintManager.h"

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
    bool cargarProyectoSprint(bool nuevo, Ticket &ticket);

    bool finalizarTicketUsuario(int idUsuario);
    bool cancelarOperacion(int opcion);

private:
    TicketArchivo _repo;
    ProyectoManager proyectoManager;
    SprintManager sprintManager;
    Proyecto p;
    Fecha f;
    Estado estado;
};
