#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"

class ReportesAdminMenuManager {
public:
    void ticketsCompletadosPorUsuario();
    void ticketsSinTerminar();
    void sprintsCompletadosPorProyecto();
    void sprintsSinTerminarPorProyecto();
};
