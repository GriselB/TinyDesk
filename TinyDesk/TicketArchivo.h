#pragma once
#include <string>
#include "utils.h"
#include "Ticket.h"

class TicketArchivo
{
public:
    TicketArchivo(std::string nombreArchivo = "ticket.dat");

    bool leer(int pos, Ticket &ticket);
    int leerTodos(Ticket tickets[], int cantidad);
    int getCantidadRegistros();
    int buscarID(int id);
    int buscarIDTicketSprintProyecto(int id, int idProyecto, int idSprint);
    int getNuevoIdTicket(int idProyecto, int idSprint);
    bool darDeBaja(int idTicket, int idProyecto, int idSprint);
    bool guardar(int pos, Ticket &t);
    bool guardarNuevo(Ticket &t);

private:
    std::string _nombreArchivo;
};
