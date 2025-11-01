#pragma once
#include <string>
#include "Ticket.h"
#include "TicketArchivo.h"

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
    void cambiarSprint();
    //Lo cree solo para poder revisar los tickets
    void listarTickets();

private:
    TicketArchivo _repo;
};
