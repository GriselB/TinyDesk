//
//  ListadoAdminMenu.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#include <iostream>
#include "ListadoAdminMenu.h"

using namespace std;

void ListadoAdminMenu::run(string titulo) {
    int opcion;

    do {
        clear();

        cout << "===== " << titulo << " ====="<<endl;
        cout << "1 - Listado de Proyectos"<<endl;
        cout << "2 - Listado de Sprints (por Proyecto)"<<endl;
        cout << "3 - Listado de Tickets (por Proyecto y Sprint)"<<endl;
        cout << "4 - Listado de usuarios" << endl;
        cout << "---------------------------"<<endl;
        cout << "0 - Volver"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                _listadoAdminManager.listarProyectos();
                break;

            case 2:
                _listadoAdminManager.listarSprintsPorProyectos();
                break;

            case 3:
                _listadoAdminManager.listarTicketsPorSprints();
                break;
                
            case 4:
                _listadoAdminManager.listarUsuarios();

            case 0:
                break;

            default:
                cout << "Opcion invalida. Elija una opcion correcta"<<endl;
                pause();
                break;
        }

    } while (opcion != 0);
}
