#pragma once

#include "ProyectoManager.h"
#include "SprintManager.h"
#include "TicketManager.h"

class ModificacionAdminMenuManager {
public:
    void modificarProyectos();
    void modificarSprintsPorProyectos();
    void modificarTicketsPorSprintsProyecto();
};
