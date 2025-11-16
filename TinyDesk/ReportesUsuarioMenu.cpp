#include <iostream>
#include "ReportesUsuarioMenu.h"

using namespace std;

void ReportesUsuarioMenu::run(string titulo) {
    int opcion;

    do {
        clear();
    cout << "      --- "<< titulo <<" ---" << endl;
    cout << "1- Porcentaje de Tickets completado del usuario" << endl;
    cout << "2- Porcentaje de Tickets sin terminar del usuario" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cout << "Has elegido el reporte " << opcion << endl;
    cout<<endl;
    //pause();

        switch (opcion) {
            case 1:
                _reportesUsuarioMenuManager.PorcentajeTicketsCompletadosDelUsuario();
                break;

            case 2:
                _reportesUsuarioMenuManager.ticketsSinTerminarDelUsuario();
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
