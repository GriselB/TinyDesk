#pragma once
#include <iostream>
#include "ReportesUsuarioMenuManager.h"

using namespace std;

void ReportesUsuarioMenuManager::porcentajeTicketsCompletadosDelUsuario(){
    clear();
    cout<<"PorcentajeTicketsCompletadosDelUsuario"<<endl;
    pause();
}

void ReportesUsuarioMenuManager::ticketsSinTerminarDelUsuario(){
    clear();
    cout<<"ticketsSinTerminarDelUsuario"<<endl;
    pause();
}

void ReportesUsuarioMenuManager::estadisticaCompletaDelUsuario(){
    clear();

    Sesion usuario;
    SesionArchivo usuarioRepo;
    TicketArchivo  ticketRepo;
    SprintArchivo  sprintRepo;

    if (!usuarioRepo.leer(usuario)) {
        cout << "Error al leer el Usuarios." << endl;
        pause();
        return;
    }

    int cantTickets = ticketRepo.getCantidadRegistros();
    if (cantTickets < 1) {
        cout << "No hay tickets registrados." << endl;
        pause();
        return;
    }

    int cantSprints = sprintRepo.getCantidadRegistros();
    if (cantSprints < 1) {
        cout << "No hay sprints registrados." << endl;
        pause();
        return;
    }

    Ticket *vecTickets = new Ticket[cantTickets];
    if (ticketRepo.leerTodos(vecTickets, cantTickets) < 1) {
        cout << "Error al leer los tickets." << endl;
        delete [] vecTickets;
        pause();
        return;
    }

    Sprint *vecSprints = new Sprint[cantSprints];
    if (sprintRepo.leerTodos(vecSprints, cantSprints) < 1) {
        cout << "Error al leer los sprints." << endl;
        delete [] vecTickets;
        delete [] vecSprints;
        pause();
        return;
    }

    //MARK: Global
    int totalGlobal = 0;
    int finalizadosGlobal = 0;
    int finalizadosATiempoGlobal = 0;
    float mediaGlobal = 0.0;
    double porcentajeGlobal = 0.0;
    double cvGlobal = 0.0;
    float mediaATiempoGlobal = 0.0;
    double porcentajeATiempoGlobal = 0.0;
    double cvGlobalATiempo = 0.0;
    float mediaGlobalTiempoCondicional = 0.0;
    double porcenajeGlobalTiempoCondicional = 0.0;
    double cvGlobalTiempoCondicional = 0.0;

    //MARK: Area del usuario
    int idArea = usuario.getArea().getIdArea();
    int totalArea = 0;
    int finalizadosArea = 0;
    int finalizadosATiempoArea = 0;
    float mediaArea = 0.0;
    double porcenajeArea = 0.0;
    double cvArea = 0.0;
    float mediaATiempoArea = 0.0;
    double porcentajeATiempoArea = 0.0;
    double cvAreaATiempo = 0.0;
    float mediaAreaTiempoCondicional = 0.0;
    double porcenajeAreaTiempoCondicional = 0.0;
    double cvAreaTiempoCondicional = 0.0;

    //MARK: Usuario
    string nombreAreaUsuario = usuario.getArea().getNombreArea();
    int totalUser = 0;
    int finalizadosUser = 0;
    int finalizadosATiempoUser = 0;
    float mediaUser = 0.0;
    double porcentajeUser = 0.0;
    double cvUser = 0.0;
    float mediaUserATiempo = 0.0;
    double porcentajeUserATiempo = 0.0;
    double cvUserATiempo = 0.0;
    float mediaUserTiempoCondicional = 0.0;
    double porcenajeUserTiempoCondicional = 0.0;
    double cvUserTiempoCondicional = 0.0;

    for (int i = 0; i < cantTickets; i++) {
        Ticket &ticket = vecTickets[i];

        bool esFinalizado = false;
        bool esFinalizadoATiempo = false;

        if (ticket.getStatus().getIdEstado() == 2) {
            esFinalizado = true;
        }

        // Global
        totalGlobal++;
        if (esFinalizado) {
            finalizadosGlobal++;
            if ( fechaMenorOIgual( ticket.getFechaFinalizada(), ticket.getFechaFin() )) {
                finalizadosATiempoGlobal++;
                esFinalizadoATiempo = true;
            }
        }

        // Area
        for (int s = 0; s < cantSprints; s++) {
            Sprint &sprint = vecSprints[s];
            if ( sprint.getIdProyecto() != ticket.getIdProyecto() ) continue;
            if ( sprint.getIdSprint() != ticket.getIdSprint() ) continue;
            if (sprint.getArea().getIdArea() == idArea) {
                totalArea++;
                if (esFinalizado) {
                    finalizadosArea++;
                    if (esFinalizadoATiempo) {
                        finalizadosATiempoArea++;
                    }
                }
                break;
            }
        }

        // Usuario
        if ( ticket.getIdEmpleado() != usuario.getIdUsuario() ) continue;
        totalUser++;
        if (esFinalizado) {
            finalizadosUser++;
            if (esFinalizadoATiempo) {
                finalizadosATiempoUser++;
            }
        }

    }

    clear();
    cout << "           =========== USUARIO ===========" << endl;

    cout << "Nombre: " << usuario.getNombre() << " " << usuario.getApellido() << endl;
    cout << " | ID: " << usuario.getIdUsuario() << " | " << endl;
    cout << " | Area: " << usuario.getArea().getNombreArea() << " |" << endl;
    cout << "----------------------         ----------------------" << endl;
    cout << endl;


    // estadisticas del usuario
    if (totalUser == 0) {
        cout << "Usted no tiene tickets asignados." << endl;
        delete [] vecTickets;
        delete [] vecSprints;
        pause();
        return;
    } else if (finalizadosUser == 0) {
        cout << "       ---> ESTADISTICAS DEL USUARIO" << endl;
        cout << "Total tickets asignados: " << totalUser << endl;
        cout << "No haz finalizado ningun ticket aun (todos pendientes)." << endl;
        delete [] vecTickets;
        delete [] vecSprints;
        pause();
        return;
    } else {
        cuentaBinomanial(mediaUser, porcentajeUser, cvUser, finalizadosUser, totalUser);

        cout << "       ---> ESTADISTICAS DEL USUARIO" << endl;
        cout << "Total tickets asignados: " << totalUser << endl;
        cout << "Total tickets finalizados: " << finalizadosUser << endl;
        cout << "Tickets aun sin finalizar: " << (totalUser - finalizadosUser) << endl;
        cout << "Total tickets finalizados a tiempo: " << finalizadosATiempoUser << endl;
        cout << "Porcentaje de tickets completados: " << porcentajeUser << "%" << endl;

        // finalizadas a tiempo - usuario -
        if (finalizadosATiempoUser > 0) {

            // a tiempo sobre el total.
            cuentaBinomanial(mediaUserATiempo, porcentajeUserATiempo, cvUserATiempo, finalizadosATiempoUser, totalUser);
            // a tiempo sobre finalizados (condicional)
            cuentaBinomanial(mediaUserTiempoCondicional, porcenajeUserTiempoCondicional, cvUserTiempoCondicional, finalizadosATiempoUser, finalizadosUser);

            cout << "Porcentaje de tickets completados a tiempo: " << porcentajeUserATiempo << "%" << endl;
            cout << "Coeficiente de variacion: " << round(cvUserATiempo * 100.0) / 100.0 << evaluarCV(cvUserATiempo) << endl;
        } else {
            cout << "El usuario no tiene ningun ticket finalizado a tiempo." << endl;
        }
    }

    // estadisticas de la empresa
    if (totalGlobal > 0 && finalizadosGlobal > 0) {

        cuentaBinomanial(mediaGlobal, porcentajeGlobal, cvGlobal, finalizadosGlobal, totalGlobal);

        // a tiempo sobre el total.
        cuentaBinomanial(mediaATiempoGlobal, porcentajeATiempoGlobal, cvGlobalATiempo, finalizadosATiempoGlobal, totalGlobal);
        // a tiempo sobre finalizados (condicional)
        cuentaBinomanial(mediaGlobalTiempoCondicional, porcenajeGlobalTiempoCondicional, cvGlobalTiempoCondicional, finalizadosATiempoGlobal, finalizadosGlobal);

    }

    // estadisticas del area del usuario
    if (totalArea > 0 && finalizadosArea > 0) {

        cuentaBinomanial(mediaArea, porcenajeArea, cvArea, finalizadosArea, totalArea);

        // a tiempo sobre el total.
        cuentaBinomanial(mediaATiempoArea, porcentajeATiempoArea, cvAreaATiempo, finalizadosATiempoArea, totalArea);
        // a tiempo sobre finalizados (condicional)
        cuentaBinomanial(mediaAreaTiempoCondicional, porcenajeAreaTiempoCondicional, cvAreaTiempoCondicional, finalizadosATiempoArea, finalizadosArea);
    }

    if (totalUser > 0 && finalizadosUser > 0){

        // USUARIO VS EMPRESA
        if(totalGlobal > 0 && finalizadosGlobal > 0) {
            float diferenciaPrcjeGlobal = porcentajeUser - porcentajeGlobal;
            float difATiempoPrcjeGlobal = porcentajeUserATiempo - porcentajeATiempoGlobal;
            float difATiempoCondGlobal = porcenajeUserTiempoCondicional - porcenajeGlobalTiempoCondicional;

            compararRendimientoUsuario("EMPRESA",
                                       diferenciaPrcjeGlobal,
                                       difATiempoPrcjeGlobal,
                                       difATiempoCondGlobal,
                                       cvUser,
                                       cvGlobal,
                                       cvUserATiempo,
                                       cvGlobalATiempo,
                                       cvUserTiempoCondicional,
                                       cvGlobalTiempoCondicional);
        }

        // USUARIO VS AREA
        if (totalArea > 0 && finalizadosArea > 0) {
            double diferenciaPrcjeArea = porcentajeUser - porcenajeArea;
            double difATiempoPrcjeArea = porcentajeUserATiempo - porcentajeATiempoArea;
            float difATiempoCondArea = porcenajeUserTiempoCondicional - porcenajeAreaTiempoCondicional;

            compararRendimientoUsuario( "AREA " + nombreAreaUsuario,
                                       diferenciaPrcjeArea,
                                       difATiempoPrcjeArea,
                                       difATiempoCondArea,
                                       cvUser,
                                       cvArea,
                                       cvUserATiempo,
                                       cvAreaATiempo,
                                       cvUserTiempoCondicional,
                                       cvAreaTiempoCondicional);
        }
    }
    cout << endl;
    cout << "====================================================" << endl;

    delete [] vecTickets;
    delete [] vecSprints;
    pause();
}


void ReportesUsuarioMenuManager::proyectosParticipaUsuario()
{
    clear();
    ProyectoArchivo proyectoArchivo;
    TicketArchivo ticketArchivo;
    Ticket ticket;
    SesionArchivo sesionArchivo;
    Sesion sesion;
    sesionArchivo.leer(sesion);
    int cantProy =  proyectoArchivo.getCantidadRegistros();
    int *vec = new int[cantProy]{};
    int id = sesion.getIdUsuario();
    int cantTickets = ticketArchivo.getCantidadRegistros();
    for (int i= 0; i < cantTickets;i++)
    {
        ticketArchivo.leer(i,ticket);
        if(id == ticket.getIdEmpleado())
        {
            int idProy = ticket.getIdProyecto();
            vec[idProy-1]++;
        }
    }
    cout<<" ------ PROYECTOS ASIGNADOS AL USUARIO ------"<<endl<<endl;
    for(int j= 0;j<cantProy;j++)
    {
        if(vec[j]>0)
            cout<<"El usuario actual esta asignado al proyecto "<<j+1<<endl;
    }
    delete [] vec;
    pause();


}
