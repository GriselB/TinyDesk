#pragma once
#include<iostream>
#include "ModificacionAdminMenuManager.h"


using namespace std;

void ModificacionAdminMenuManager::modificarProyectos(){
    ProyectoManager proy;
    int opcion;
    do {
        clear();

        cout << "===== Modificar Proyecto ====="<<endl;
        cout << "1 - Finalizar Proyecto"<<endl;
        cout << "2 - Dar de Baja el Proyecto"<<endl;
        cout << "3 - Dar de Alta el Proyecto"<<endl;
        cout << "---------------------------"<<endl;
        cout << "0 - Volver"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                proy.finalizarProyecto();
                break;

            case 2:
               proy.bajaLogicaProyecto();
                break;

            case 3:
               proy.altaLogicaProyecto();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida. Elija una opcion correcta"<<endl;
                pause();
                break;
        }

    } while (opcion != 0);
}
void ModificacionAdminMenuManager::modificarSprintsPorProyectos(){
   SprintManager sprint;
    int opcion;
    do {
        clear();

        cout << "===== Modificar Sprint ====="<<endl;
        cout << "1 - Finalizar Sprint"<<endl;
        cout << "2 - Baja Logica de Sprint"<<endl;
        cout << "---------------------------"<<endl;
        cout << "0 - Volver"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                sprint.finalizarSprint();
                break;

            case 2:
                sprint.eliminarSprintLogico();
                break;

            case 0:
                break;

            default:
                cout << "Opcion invalida. Elija una opcion correcta"<<endl;
                pause();
                break;
        }

    } while (opcion != 0);
}
void ModificacionAdminMenuManager::modificarTicketsPorSprintsProyecto(){
}

void ModificacionAdminMenuManager::modificarUsuario(){
    UsuarioManager userMgr;
    userMgr.eliminarUsuario();
}
