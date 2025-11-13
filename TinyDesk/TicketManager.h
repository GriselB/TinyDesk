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
    void finalizarTicket();

    void modificarDescripcion();
    void modificarPrioridad();
    void modificarStatus();
    void asignarNuevoEmpleado();
    void listarTickets();
    bool finalizarTicketUsuario(int idProyecto, int idSprint, int idTicket, int idUsuario);

private:
    TicketArchivo _repo;
    ProyectoManager proyectoM;
    SprintManager sprintM;
};
