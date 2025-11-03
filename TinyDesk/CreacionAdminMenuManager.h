#pragma once

#include "TicketManager.h"
#include "ProyectoManager.h"
#include "SprintManager.h"

class CreacionAdminMenuManager {
public:
    void crearProyectos();
    void crearSprintsPorProyectos();
    void crearTicketsPorSprints();
};
