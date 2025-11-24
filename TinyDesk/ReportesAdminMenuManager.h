#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"
#include "UsuarioManager.h"
#include <cmath>

class ReportesAdminMenuManager {
public:
    void estadisticasDetalladasDeUnUsuario();
    void ticketsSinTerminar();
    void sprintsCompletadosPorProyecto();
    void sprintsAtrasadosArea();
    void proyectosCompletados();
    void proyectosFinalizadosATiempo();
    void proyectosSinSprintAsignados();
    void progresoTicketsPorProyecto();
};
