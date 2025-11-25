#include <iostream>
#include "ReportesUsuarioMenu.h"

using namespace std;

void ReportesUsuarioMenu::run(string titulo) {
    int opcion;

    do {
        clear();
    cout << "      --- "<< titulo <<" ---" << endl;
    cout << "1 - Porcentaje de Tickets completado del usuario" << endl;
    cout << "2 - Tickets proximos a vencerse por usuario" << endl;
    cout << "3 - Estadistica Completa del Usuario" << endl;
    cout << "4 - Proyectos en los que participa el Usuario" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cout << "Has elegido el reporte " << opcion << endl;
    cout<<endl;
    pause();

        switch (opcion) {
            case 1:
                _reportesUsuarioMenuManager.porcentajeTicketsCompletadosDelUsuario();
                break;

            case 2:
                _reportesUsuarioMenuManager.ticketsProximosAvencerseXusuario();
                break;

            case 3:
                _reportesUsuarioMenuManager.estadisticaCompletaDelUsuario();
                break;

            case 4:
                _reportesUsuarioMenuManager.proyectosParticipaUsuario();

            case 0:
                break;

            default:
                cout << "Opcion invalida. Elija una opcion correcta"<<endl;
                pause();
                break;
        }

    } while (opcion != 0);
}
