#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"

class ReportesAdminMenuManager {
public:
    void PorcentajeTicketsCompletadosPorUsuario();
    void ticketsSinTerminar();
    void sprintsCompletadosPorProyecto();
    void sprintsSinTerminarPorProyecto();
};
