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
        cout << "No hay usuarios registrados." << endl;
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

    // Global
    int totalGlobal = 0;
    int finalizadosGlobal = 0;
    int finalizadosATiempoGlobal = 0;
    float mediaGlobal = 0.0;
    double porcentajeGlobal = 0.0;
    double cvGlobal = 0.0;
    float mediaATiempoGlobal = 0.0;
    double porcentajeATiempoGlobal = 0.0;
    double cvGlobalATiempo = 0.0;

    // Area del usuario
    int idArea = usuario.getArea().getIdArea();
    int totalArea = 0;
    int finalizadosArea = 0;
    int finalizadosATiempoArea = 0;
    float mediaArea = 0.0;
    float porcenajeArea = 0.0;
    float cvArea = 0.0;
    float mediaATiempoArea = 0.0;
    double porcentajeATiempoArea = 0.0;
    double cvAreaATiempo = 0.0;

    // Usuario
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

    for (int i = 0; i < cantTickets; i++) {
        Ticket &t = vecTickets[i];

        bool esFinalizado = false;
        bool esFinalizadoATiempo = false;

        if (t.getStatus().getIdEstado() == 2) {
            esFinalizado = true;
        }

        // Global
        totalGlobal++;
        if (esFinalizado) {
            finalizadosGlobal++;
            if ( fechaMenorOIgual( t.getFechaFinalizada(), t.getFechaFin() )) {
                finalizadosATiempoGlobal++;
                esFinalizadoATiempo = true;
            }
        }

        // Area
        for (int s = 0; s < cantSprints; s++) {
            Sprint &sp = vecSprints[s];
            if ( sp.getIdProyecto() != t.getIdProyecto() ) continue;
            if ( sp.getIdSprint() != t.getIdSprint() ) continue;
            if (sp.getArea().getIdArea() == idArea) {
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
        if ( t.getIdEmpleado() != usuario.getIdUsuario() ) continue;
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
    cout << " | ID: " << usuario.getIdUsuario() << endl;
    cout << " | Area: " << usuario.getArea().getNombreArea() << endl;
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
        mediaUser = finalizadosUser / float(totalUser);
        porcentajeUser = round(mediaUser * 10000.0) / 100.0;
        double varUsr = totalUser * mediaUser * (1 - mediaUser);
        double desvioUsr = sqrt(varUsr);
        cvUser = (desvioUsr / finalizadosUser) * 100.0;

        cout << "       ---> ESTADISTICAS DEL USUARIO" << endl;
        cout << "Total tickets asignados: " << totalUser << endl;
        cout << "Total tickets finalizados: " << finalizadosUser << endl;
        cout << "Tickets aun sin finalizar: " << (totalUser - finalizadosUser) << endl;
        cout << "Total tickets finalizados a tiempo: " << finalizadosATiempoUser << endl;
        cout << "Porcentaje de tickets completados: " << porcentajeUser << "%" << endl;

        // finalizadas a tiempo - usuario -
        if (finalizadosATiempoUser > 0) {
            mediaUserATiempo = finalizadosATiempoUser / float(finalizadosUser);
            porcentajeUserATiempo = round(mediaUserATiempo * 10000.0) / 100.0;

            double varUsrTime = finalizadosUser * mediaUserATiempo * (1 - mediaUserATiempo);
            double desvioUsrTime = sqrt(varUsrTime);
            cvUserATiempo = (desvioUsrTime / finalizadosATiempoUser) * 100.0;

            cout << "Porcentaje de tickets completados a tiempo: " << porcentajeUserATiempo << "%" << endl;
            cout << "Coeficiente de variacion: " << round(cvUserATiempo * 100.0) / 100.0 << evaluarCV(cvUserATiempo) << endl;
        } else {
            cout << "El usuario no tiene ningun ticket finalizado a tiempo." << endl;
        }
    }

    // estadisticas de la empresa
    if (totalGlobal > 0 && finalizadosGlobal > 0) {
        mediaGlobal = finalizadosGlobal / float(totalGlobal);
        porcentajeGlobal = round(mediaGlobal * 10000.0) / 100.0;
        double varGlob = totalGlobal * mediaGlobal * (1 - mediaGlobal);
        double desvioGlob = sqrt(varGlob);
        cvGlobal = (desvioGlob / finalizadosGlobal) * 100.0;

        // a tiempo
        mediaATiempoGlobal = finalizadosATiempoGlobal / float(finalizadosGlobal);
        porcentajeATiempoGlobal = round(mediaATiempoGlobal * 10000.0) / 100.0;
        double varGlobATiempo = finalizadosGlobal * mediaATiempoGlobal * (1 - mediaATiempoGlobal);
        double desvioGlobATiempo = sqrt(varGlobATiempo);
        cvGlobalATiempo = (desvioGlobATiempo / finalizadosATiempoGlobal) * 100.0;
    }

    // estadisticas del area del usuario
    if (totalArea > 0 && finalizadosArea > 0) {
        mediaArea = finalizadosArea / float(totalArea);
        porcenajeArea = round(mediaArea * 10000.0) / 100.0;
        double varArea = totalArea * mediaArea * (1 - mediaArea);
        double desvioArea = sqrt(varArea);
        cvArea = (desvioArea / finalizadosArea) * 100.0;

        // a tiempo
        mediaATiempoArea = finalizadosATiempoArea / float(finalizadosArea);
        porcentajeATiempoArea = round(mediaATiempoArea * 10000.0) / 100.0;
        double varAreaATiempo = finalizadosArea * mediaATiempoArea * (1 - mediaATiempoArea);
        double desvioAreaATiempo = sqrt(varAreaATiempo);
        cvAreaATiempo = (desvioAreaATiempo / finalizadosATiempoArea) * 100.0;
    }

    if (totalUser > 0 && finalizadosUser > 0){

        // USUARIO VS EMPRESA
        if(totalGlobal > 0 && finalizadosGlobal > 0) {
            float diferenciaPrcjeGlobal = porcentajeUser - porcentajeGlobal;
            float difATiempoPrcjeGlobal = porcentajeUserATiempo - porcentajeATiempoGlobal;

            compararRendimientoUsuario("EMPRESA",
                                       diferenciaPrcjeGlobal,
                                       difATiempoPrcjeGlobal,
                                       cvUser,
                                       cvGlobal,
                                       cvUserATiempo,
                                       cvGlobalATiempo);
        }

        // USUARIO VS AREA
        if (totalArea > 0 && finalizadosArea > 0) {
            double diferenciaPrcjeArea = porcentajeUser - porcenajeArea;
            double difATiempoPrcjeArea = porcentajeUserATiempo - porcentajeATiempoArea;

            compararRendimientoUsuario( "AREA",
                                       diferenciaPrcjeArea,
                                       difATiempoPrcjeArea,
                                       cvUser,
                                       cvArea,
                                       cvUserATiempo,
                                       cvAreaATiempo);
        }
    }
    cout << endl;
    cout << "====================================================" << endl;

    delete [] vecTickets;
    delete [] vecSprints;
    pause();
}
