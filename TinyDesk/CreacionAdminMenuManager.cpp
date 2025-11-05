#pragma once
#include "CreacionAdminMenuManager.h"

using namespace std;

void CreacionAdminMenuManager::crearProyectos(){
    ProyectoManager proy;
    proy.crearProyecto();
}
void CreacionAdminMenuManager::crearSprintsPorProyectos(){
  SprintManager sprint;
  sprint.crearSprint();
}
void CreacionAdminMenuManager::crearTicketsPorSprintsProyecto(){
}
