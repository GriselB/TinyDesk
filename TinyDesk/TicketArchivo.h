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
    int getNuevoID();
    bool guardar(Ticket ticket);
    bool eliminar(int pos);
    bool yaExisteTicketEmpleadoSprint(Ticket &ticket);

private:
    std::string _nombreArchivo;
};
