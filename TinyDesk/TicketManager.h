#pragma once
#include <string>
#include "Ticket.h"
#include "TicketArchivo.h"
#include "ProyectoManager.h"
#include "SprintManager.h"
#include "UsuarioManager.h"

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
    void cargarProyectoSprint(bool nuevo, Ticket &ticket, int &pos);

    bool finalizarTicketUsuario(int idUsuario);
    bool cancelarOperacion(int opcion);

private:
    TicketArchivo _repo;
    ProyectoArchivo _repoProyecto;
    SprintArchivo _repoSprint;
    UsuarioArchivo _repoUsuario;
    Proyecto p;
    Fecha f;
    Estado estado;
};
