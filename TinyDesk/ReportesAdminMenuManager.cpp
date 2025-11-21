#pragma once
#include <iostream>
#include "ReportesAdminMenuManager.h"

using namespace std;

void ReportesAdminMenuManager::PorcentajeTicketsCompletadosPorUsuario(){
    clear();
    UsuarioArchivo usuarioRepo;
    TicketArchivo ticketRepo;

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
        if(user.getIdRol() == 1) continue;

        int totalTicketsUsuario = 0;
        int finalizados = 0;
        int finalizadosATiempo = 0;

        for(int j=0; j<leidos ; j++){
            Ticket &ticket = vecTickets[j];

            //if(!ticket.getActivo()) continue;  ‼️ verificar cuando modifiquen estado

            if( ticket.getIdEmpleado() == user.getIdUsuario() ) {
                totalTicketsUsuario ++;
                // cambiar verificacion con estado una vez que lo incorporen
                if(ticket.getStatus() == 2){
                    finalizados ++;
                    if(fechaMenorOIgual(ticket.getFechaFinalizada(), ticket.getFechaFin())){
                        finalizadosATiempo++;
                    }
                }

            }
        }

        cout << "Usuario: " << user.getNombre() << " " << user.getApellido() << endl;
        cout << "ID: " << user.getIdUsuario() << endl;
        cout << "Area: " << user.getArea().getNombreArea() << endl;
        cout << "Total tickets asignados: " << totalTicketsUsuario << endl;
        cout << "Total tickets finalizados: " << finalizados << endl;

        if(totalTicketsUsuario>0) {
            if(finalizados > 0){
                float media = finalizados / float(totalTicketsUsuario);

                double porcentaje = round(media * 10000.0) / 100.0;
                double varianza = totalTicketsUsuario * media * (1-media);
                double desvio = sqrt(varianza);
                double cv = (desvio / finalizados) * 100.0;

                cout << "___ Tickets Finalizados en total ___" << endl;
                cout << "Porcentaje completados: " << porcentaje << "%" << endl;
                cout << "Desvío estándar: "
                << round(desvio * 10000.0) / 10000.0 << "  -> Dispersión del promedio" << endl;
                cout << "Coeficiente de variación: "
                << round(cv * 100.0) / 100.0 << evaluarCV(cv) << endl;

                if(finalizadosATiempo > 0){
                    float mediaATiempo = finalizadosATiempo / float(totalTicketsUsuario);
                    double porcentajeATiempo = round(mediaATiempo * 10000.0) / 100.0;
                    double varianzaATiempo = totalTicketsUsuario * mediaATiempo * (1 - mediaATiempo);
                    double desvioATiempo = sqrt(varianzaATiempo);
                    double cvATiempo = (desvioATiempo / finalizadosATiempo) * 100.0;

                    cout << "___ Tickets Finalizados A Tiempo ___" << endl;
                    cout << "Porcentaje, a tiempo: " << porcentajeATiempo << "%" << endl;
                    cout << "Desvío, a tiempo: "
                    << round(desvioATiempo * 10000.0) / 10000.0 << "  -> Dispersión del promedio" << endl;
                    cout << "Coeficiente de variación, a tiempo: "
                    << round(cvATiempo * 100.0) / 100.0 << evaluarCV(cvATiempo) << endl;
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

void ReportesAdminMenuManager::proyectosCompletados()
{
    clear();
    int total;
    float completados, resultado;
    ProyectoArchivo proyectoArchivo;
    total = proyectoArchivo.getCantidadRegistros();
    completados = 0;
    for (int i=0;i<total;i++)
    {
        if(proyectoArchivo.leer(i).getIdEstado()== 2)
            completados++;
    }
    resultado = (completados/total)*100;
    cout<<" ------------ PROYECTOS COMPLETADOS ------------ "<<endl;
    cout<<"La cantidad de proyectos completados es del: "<<resultado<<"%"<<endl;
    cout<<"La cantidad de proyectos no completados es del: "<<100-resultado<<"%"<<endl;
    cout<<completados<<endl;
    cout<<total<<endl;
    pause();

}

void ReportesAdminMenuManager::proyectosFinalizadosATiempo()
{
    clear();
    int total;
    float finalizados, finalizadosATiempo, resultado;
    Fecha fin, finalizada;
    ProyectoArchivo proyectoArchivo;
    total = proyectoArchivo.getCantidadRegistros();
    finalizados = 0;
    finalizadosATiempo = 0;
    for(int i=0;i<total;i++)
    {
        if(proyectoArchivo.leer(i).getIdEstado()==2)
        {
            finalizados++;
            fin=proyectoArchivo.leer(i).getFechaFin();
            finalizada=proyectoArchivo.leer(i).getFechaFinalizada();
            if(fechaMenorOIgual(finalizada,fin))
                finalizadosATiempo++;
        }
    }
    resultado=(finalizadosATiempo/finalizados)*100;
    if(finalizados == 0 )
        resultado = 0;
    cout<<" ------------ PROYECTOS FINALIZADOS A TIEMPO ------------ "<<endl;
    cout<<"El porcentaje de proyectos finalizados a tiempo es de: "<<resultado<<"%"<<endl;
    cout<<"El porcentaje de proyectos finalizados fuera de tiempo es de: "<<100-resultado<<"%"<<endl;
    pause();
}
