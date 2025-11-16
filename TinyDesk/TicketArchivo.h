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
    int getNuevoID(int idProyecto, int idSprint);
    int buscarIDTicketSprintProyecto(int id, int idProyecto, int idSprint);
    int getNuevoIdTicketSprint(int idProyecto, int idSprint);
    bool guardar(Ticket ticket);
    bool darDeBaja(int idTicket, int idProyecto, int idSprint);
    bool guardarCambios(int pos, Ticket &t);

private:
    std::string _nombreArchivo;
};
