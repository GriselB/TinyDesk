#pragma once
#include <iostream>
#include "ReportesAdminMenuManager.h"

using namespace std;

void ReportesAdminMenuManager::PorcentajeTicketsCompletadosPorUsuario(){
    clear();
    UsuarioArchivo usuarioRepo;
    TicketArchivo ticketRepo;
    Fecha fecha;
    const string AREAS[5] = {"Administracion", "Backend", "Frontend", "QA", "UX/UI"};
    
    int cantidadUsuarios = usuarioRepo.getCantidadRegistros();
    if(cantidadUsuarios < 1){
        cout << "No hay usuarios registrados" << endl;
        pause();
        return;
    }
    
    int cantidadTicket = ticketRepo.getCantidadRegistros();
    if(cantidadTicket < 1){
        cout << "No hay tickets registrados" << endl;
        pause();
        return;
    }
    
    Ticket *vecTickets = new Ticket[cantidadTicket];
    int leidos = ticketRepo.leerTodos(vecTickets, cantidadTicket);
    if(leidos < 1){
        cout << "Error al leer los tickets" << endl;
        delete [] vecTickets;
        pause();
        return;
    }
    cout << "------- ESTADISTICAS DE TICKETS COMPLETADOS POR USUARIO -------" << endl;
    
    for(int i=0; i<cantidadUsuarios; i++){
        Usuario user = usuarioRepo.leer(i);
        if( !user.getActivo() ) continue;
        
        int totalTicketsUsuario = 0;
        int finalizados = 0;
        int finalizadosATiempo = 0;
        
        for(int j=0; j<leidos ; j++){
            Ticket &ticket = vecTickets[j];
            
            //if(!ticket.getActivo()) continue;  ‼️ verificar cuando modifiquen estado
            
            if( ticket.getIdEmpleado() == user.getIdUsuario() ) {
                totalTicketsUsuario ++;
                // cambiar verificacion con estado una vez que lo incorporen
                if(ticket.getStatus() == "Finalizado"){
                    finalizados ++;
                    if(fecha.fechaMenorOIgual(ticket.getFechaFinalizada(), ticket.getFechaFin())){
                        finalizadosATiempo++;
                    }
                }
                
            }
        }
        
        cout << "Usuario: " << user.getNombre() << " " << user.getApellido() << endl;
        cout << "ID: " << user.getIdUsuario() << endl;
        cout << "Area: " << AREAS[user.getIdArea()-1] << endl;
        cout << "Total tickets asignados: " << totalTicketsUsuario << endl;
        cout << "Total tickets finalizados: " << finalizados << endl;
        
        if(totalTicketsUsuario>0) {
            if(finalizados > 0){
                float media = finalizados / float(totalTicketsUsuario);
                
                double porcentaje = round(media * 10000.0) / 100.0;
                double varianza = totalTicketsUsuario * media * (1-media);
                double desvio = sqrt(varianza);
                double cv = (desvio / finalizados) * 100.0;
                
                cout << "--- Tickets Finalizados en total ---" << endl;
                cout << "Porcentaje completados: " << porcentaje << "%" << endl;
                cout << "Desvío estándar: " << round(desvio * 10000.0) / 10000.0
                << "  -> Dispersión del desempeño" << endl;
                cout << "Coeficiente de variación: " << round(cv * 100.0) / 100.0
                << "% -> Consistencia del desempeño" << endl;
                
                if(finalizadosATiempo > 0){
                    cout << "--- Tickets Finalizados A Tiempo ---" << endl;
                    
                    float mediaATiempo = finalizadosATiempo / float(totalTicketsUsuario);
                    double porcentajeATiempo = round(mediaATiempo * 10000.0) / 100.0;
                    double varianzaATiempo = totalTicketsUsuario * mediaATiempo * (1 - mediaATiempo);
                    double desvioATiempo = sqrt(varianzaATiempo);
                    double cvATiempo = (desvioATiempo / finalizadosATiempo) * 100.0;
                    
                    
                    cout << "Porcentaje a tiempo: " << porcentajeATiempo << "%" << endl;
                    cout << "Desvío a tiempo: " << round(desvioATiempo * 10000.0) / 10000.0 << endl;
                    cout << "Coeficiente de variación a tiempo: "
                    << round(cvATiempo * 100.0) / 100.0
                    << "% -> Consistencia en cumplir dentro de la fecha" << endl;
                } else {
                    cout << "El usuario no completó ninguna tarea a tiempo." << endl;
                }
            }
            else {
                cout << "El usuario no completó ninguna tarea." << endl;
            }
            
        } else {
            cout << "El Usuario no tiene Tickets Asignados." << endl;
        }
        
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
