//
//  ListadoAdminManager.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#pragma once

#include "Ticket.h"

#include "ProyectoManager.h"
#include "UsuarioManager.h"
#include "SprintManager.h"

class ListadoAdminManager {
public:
    void listarProyectos();
    void listarSprintsPorProyectos();
    void listarTicketsPorSprints();
    void listarUsuarios();
};
