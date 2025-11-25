#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"
#include "UsuarioManager.h"
#include "Sesion.h"
#include <cmath>

class ReportesUsuarioMenuManager {
public:
    void porcentajeTicketsCompletadosDelUsuario();
    void ticketsSinTerminarDelUsuario();
    void estadisticaCompletaDelUsuario();
    void proyectosParticipaUsuario();
};
