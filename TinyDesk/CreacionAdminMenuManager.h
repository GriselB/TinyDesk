#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"

class CreacionAdminMenuManager {
public:
    void crearProyectos();
    void crearSprintsPorProyectos();
    void crearTicketsPorSprintsProyecto();
};
