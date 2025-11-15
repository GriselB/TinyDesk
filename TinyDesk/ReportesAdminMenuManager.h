#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"
#include "UsuarioManager.h"
#include <cmath>

class ReportesAdminMenuManager {
public:
    void PorcentajeTicketsCompletadosPorUsuario();
    void ticketsSinTerminar();
    void sprintsCompletadosPorProyecto();
    void sprintsSinTerminarPorProyecto();
};
