#include <iostream>
#include "ModificacionAdminMenu.h"

using namespace std;

void ModificacionAdminMenu::run(string titulo) {
    int opcion;

    do {
        clear();

        cout << "===== " << titulo << " ====="<<endl;
        cout << "1 - Modificar Proyecto"<<endl;
        cout << "2 - Modificar Sprint (por proyecto)"<<endl;
        cout << "3 - Modificacion Ticket (por sprint y proyecto)"<<endl;
        cout << "---------------------------"<<endl;
        cout << "0 - Volver"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                _modificacionAdminMenuManager.modificarProyectos();
                break;

            case 2:
                _modificacionAdminMenuManager.modificarSprintsPorProyectos();
                break;

            case 3:
                _modificacionAdminMenuManager.modificarTicketsPorSprintsProyecto();
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

