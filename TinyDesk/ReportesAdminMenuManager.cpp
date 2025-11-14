#pragma once
#include <iostream>
#include "ReportesAdminMenuManager.h"

using namespace std;

void ReportesAdminMenuManager::PorcentajeTicketsCompletadosPorUsuario(){
    clear();
    UsuarioArchivo usuarioRepo;
    TicketArchivo ticketRepo;
    const string AREAS[5] = {"Administracion", "Backend", "Frontend", "QA", "UX/UI"};
    
    int cantidadUsuarios = usuarioRepo.getCantidadRegistros();
    if(cantidadUsuarios < 1){
        cout << "No hay usuarios registrados" << endl;
        pause();
        return;;
    }
    
    int cantidadTicket = ticketRepo.getCantidadRegistros();
    if(cantidadTicket < 1){
        cout << "No hay tickets registrados" << endl;
        pause();
        return;;
    }
    
    Ticket *vecTickets = new Ticket[cantidadTicket];
    int ticketsLeidos = ticketRepo.leerTodos(vecTickets, cantidadTicket);
    if(ticketsLeidos < 1){
        cout << "Error al leer los tickets" << endl;
        delete [] vecTickets;
        pause();
        return;;
    }
    cout << "------- PORCENTAJE DE TICKETS COMPLETADOS POR USUARIO -------" << endl;
    
    for(int i=0; i<cantidadUsuarios; i++){
        Usuario user = usuarioRepo.leer(i);
        if( !user.getActivo() ) continue;
        int total = 0;
        int finalizados = 0;
        
        for(int j=0; j<ticketsLeidos ; j++){
            Ticket &ticket = vecTickets[j];
            
            //if(!ticket.getActivo()) continue;  ??????!!!!???? verificar cuando modifiquen estado
            
            if( ticket.getIdEmpleado() == user.getIdUsuario() ) {
                total ++;
                // cambiar verificacion con estado una vez que lo incorporen
                if(ticket.getFechaFinalizada().getAnio()!=0 || ticket.getStatus() == "Finalizado"){
                    finalizados ++;
                }
            }
        }
        
        float porcentaje = 0.0;
        
        if(total > 0){
            porcentaje = (finalizados * 100.0) / float(total);
        }
        
        cout << "Usuario: " << user.getNombre() << " " << user.getApellido() << endl;
        cout << "ID: " << user.getIdUsuario() << endl;
        cout << "Area: " << AREAS[user.getIdArea()-1] << endl;
        cout << "Total tickets asignados: " << total << endl;
        cout << "Total tickets finalizados: " << finalizados << endl;
        cout << "PORCENTAJE TICKETS COMPLETADOS: " << porcentaje << "%" << endl;
        cout << "------------------------------------------------------" << endl;

    }
    
    delete [] vecTickets;
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
