#include <iostream>
#include "ReportesAdminMenu.h"

using namespace std;

void ReportesAdminMenu::run(string titulo) {
    int opcion;

    do {
        clear();
    cout << "      --- "<< titulo <<" ---" << endl;
    cout << "1- Estadistica Completa de un Usuario seleccionado" << endl;
    cout << "2- Porcentaje de Tickets sin terminar" << endl;
    cout << "3- Porcentaje de Sprints completados por proyecto" << endl;
    cout << "4- Sprints Atrasados por area" << endl;
    cout << "5- Porcentaje de Proyectos completados" << endl;
    cout << "6- Porcentaje de proyectos finalizados a tiempo" << endl;
    cout << "7- Porcentaje de proyectos sin Sprint asignados" << endl;
    cout << "8- Avances de proyecto (en relacion a los tickets)" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
    cout << "Opcion: ";
    cin >> opcion;
    cout << "Has elegido el reporte " << opcion << endl;
    cout<<endl;
    //pause();

        switch (opcion) {
            case 1:
                _reportesAdminMenuManager.estadisticasDetalladasDeUnUsuario();
                break;

            case 2:
                _reportesAdminMenuManager.ticketsSinTerminar();
                break;

            case 3:
                _reportesAdminMenuManager.sprintsCompletadosPorProyecto();
                break;

            case 4:
                _reportesAdminMenuManager.sprintsAtrasadosArea();
                break;

            case 5:
                _reportesAdminMenuManager.proyectosCompletados();
                break;

            case 6:
                _reportesAdminMenuManager.proyectosFinalizadosATiempo();
                break;

            case 7:
                _reportesAdminMenuManager.proyectosSinSprintAsignados();
                break;

            case 8:
                _reportesAdminMenuManager.progresoTicketsPorProyecto();
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

