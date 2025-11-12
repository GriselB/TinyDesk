#pragma once
#include <iostream>
#include "ReportesAdminMenuManager.h"

using namespace std;

void ReportesAdminMenuManager::ticketsCompletadosPorUsuario(){
cout<<"ticketsCompletadosPorUsuario"<<endl;
pause();
}
void ReportesAdminMenuManager::ticketsSinTerminar(){
cout<<"ticketsSinTerminar"<<endl;
pause();
}
void ReportesAdminMenuManager::sprintsCompletadosPorProyecto(){

 clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();

    cout << "            ----- SPRINTS COMPLETADOS POR PROYECTO -----\n\n";

    if (cantProyectos <= 0) {
        cout << "No hay proyectos registrados.\n";
        pause();
        return;
    }

    if (cantSprints <= 0) {
        cout << "No hay sprints registrados.\n";
        pause();
        return;
    }

    int *idsProyecto = new int[cantProyectos];
    int *totalSprints = new int[cantSprints]{0};
    int *finalizados = new int[cantSprints]{0};

    
    for (int i = 0; i < cantProyectos; i++) {
        Proyecto p = archivoProyecto.leer(i);
        idsProyecto[i] = p.getIdProyecto();
    }


    for (int j = 0; j < cantSprints; j++) {
        Sprint s = archivoSprint.leer(j);

        for (int i = 0; i < cantProyectos; i++) {
            if (idsProyecto[i] == s.getIdProyecto()) {

                totalSprints[i]++;

                if (s.getIdEstado() == 2) {
                    finalizados[i]++;
                }

            }
        }
    }

    for (int i = 0; i < cantProyectos; i++) {

        Proyecto p = archivoProyecto.leer(i);

        cout << "Proyecto " << p.getIdProyecto()
             << " - " << p.getNombre() << endl;

        if (totalSprints[i] == 0) {
            cout << "  No tiene sprints asignados "<< endl;
            continue;
        }

        float porcentaje = (finalizados[i] * 100.0f) / totalSprints[i];

        cout << "  Sprints totales:   " << totalSprints[i] << endl;
        cout << "  Finalizados:       " << finalizados[i] << endl;
        cout << "  Progreso:          " << porcentaje << "%" << endl;
        cout << "------------------------------------------"<< endl;
    }
    
    
    delete[] idsProyecto;
    delete[] totalSprints;
    delete[] finalizados;
    pause();
}
void ReportesAdminMenuManager::sprintsSinTerminarPorProyecto(){
cout<<"sprintsSinTerminarPorProyecto"<<endl;
pause();
}
