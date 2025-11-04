#include <iostream>
#include "CreacionAdminMenu.h"

using namespace std;

void CreacionAdminMenu::run(string titulo) {
    int opcion;

    do {
        clear();

        cout << "===== " << titulo << " ====="<<endl;
        cout << "1 - Crear Proyecto"<<endl;
        cout << "2 - Crear Sprint (por proyecto)"<<endl;
        cout << "3 - Crear Ticket (por sprint y proyecto)"<<endl;
        cout << "---------------------------"<<endl;
        cout << "0 - Volver"<<endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                _creacionAdminMenuManager.crearProyectos();
                break;

            case 2:
                _creacionAdminMenuManager.crearSprintsPorProyectos();
                break;

            case 3:
                _creacionAdminMenuManager.crearTicketsPorSprintsProyecto();
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

