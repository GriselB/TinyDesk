//
//  TareasUsuarioManager.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#include <iostream>
#include "TareasUsuarioManager.h"

using namespace std;

void TareasUsuarioManager::listarTareasUsuario() {
    Sesion ses;
    SesionArchivo sesArch;
    if (!sesArch.leer(ses)) {
        cout << "Error al obtener datos del Usuario"<<endl;
        pause();
        return;
    }

    TicketManager ticketMgr;
    ProyectoArchivo archivoProyecto;
    SprintArchivo   archivoSprint;
    TicketArchivo   archivoTicket;

    int cantProy = archivoProyecto.getCantidadRegistros();
    int cantSpr  = archivoSprint.getCantidadRegistros();
    int cantTick = archivoTicket.getCantidadRegistros();

    bool hayTicket = false;
    int totalTicketsPendientes = 0;

    for (int i = 0; i < cantProy; ++i) {
        Proyecto proy = archivoProyecto.leer(i);
        if (proy.getIdEstado() == -1) continue;

        bool imprimioEncabezadoProyecto = false;

        for (int j = 0; j < cantSpr; ++j) {
            int pos = archivoSprint.buscarID(j, i);
            Sprint spr = archivoSprint.leer(pos);
            if(spr.getIdSprint() == -1) continue;
            if (spr.getIdEstado()!= 2) continue;
            if (spr.getIdProyecto() != proy.getIdProyecto()) continue;

            bool imprimioEncabezadoSprint = false;

            for (int k = 0; k < cantTick; ++k) {
                Ticket t;
                int pos = archivoTicket.buscarIDTicketSprintProyecto(k, i, j);
                if (!archivoTicket.leer(pos, t)) continue;
                if (t.getStatus().getIdEstado() == 0) continue;
                if (t.getIdProyecto() != proy.getIdProyecto()) continue;
                if (t.getIdSprint()   != spr.getIdSprint()) continue;
                if (t.getIdEmpleado() != ses.getIdUsuario()) continue;

                if (!imprimioEncabezadoProyecto) {
                    cout << "=== PROYECTO " << proy.getIdProyecto() << " - " << proy.getNombre() << " ==="<<endl;
                    imprimioEncabezadoProyecto = true;
                }
                if (!imprimioEncabezadoSprint) {
                    cout << "  -- Sprint #" << spr.getIdSprint() << endl;
                    imprimioEncabezadoSprint = true;
                }

                ticketMgr.mostrarTicket(t);
                cout << "-------------------------------"<<endl;
                cout << "-------------------------------"<<endl;
                hayTicket = true;
                totalTicketsPendientes++;
            }
        }
    }

    cout << "===================================================="<<endl;
    if(totalTicketsPendientes){
        cout << "Usted tiene " << totalTicketsPendientes << " tickets pendientes." << endl;
    }
    if (!hayTicket) {
        cout << "Hora de pedir tareas nuevas. Usted no tiene tareas asignadas."<<endl;
    }

    pause();
}

void TareasUsuarioManager::finalizarTicket() {
    clear();

    Sesion ses;
    SesionArchivo sesArch;
    if (!sesArch.leer(ses)) {
        cout << "Error al obtener la sesión.\n";
        pause();
        return;
    }

    int idUsuario = ses.getIdUsuario();

    ProyectoArchivo archivoProyecto;
    SprintArchivo   archivoSprint;
    TicketArchivo   archivoTicket;
    TicketManager tMgr;

    int cantProy = archivoProyecto.getCantidadRegistros();
    int cantSpr  = archivoSprint.getCantidadRegistros();
    int cantTick = archivoTicket.getCantidadRegistros();

    bool hayTicket = false;

    cout << "=========== TUS TICKETS ===========" <<endl;

    for (int i = 0; i < cantProy; i++) {
        Proyecto proy = archivoProyecto.leer(i);
        if (proy.getIdProyecto() == -1) continue;

        bool imprimioProy = false;

        for (int j = 0; j < cantSpr; j++) {
            int pos = archivoSprint.buscarID(j, i);
            Sprint spr = archivoSprint.leer(pos);
            if (spr.getIdEstado() == 0 || spr.getIdEstado() == 2) continue;
            if (spr.getIdProyecto() != proy.getIdProyecto()) continue;

            bool imprimioSprint = false;

            for (int k = 0; k < cantTick; k++) {
                Ticket t;
                int pos = archivoTicket.buscarIDTicketSprintProyecto(k, i, j);
                if (!archivoTicket.leer(pos, t)) continue;

                if (t.getStatus().getIdEstado() == 0) continue;
                if (t.getIdEmpleado() != idUsuario) continue;
                if (t.getIdProyecto() != proy.getIdProyecto()) continue;
                if (t.getIdSprint()   != spr.getIdSprint()) continue;

                // Mostrar encabezados
                if (!imprimioProy) {
                    cout << "---- PROYECTO " << proy.getIdProyecto() << ": " << proy.getNombre() << endl;
                    imprimioProy = true;
                }

                if (!imprimioSprint) {
                    cout << "  -- Sprint " << spr.getNombre() << endl;
                    imprimioSprint = true;
                }

                // Mostrar ticket
                tMgr.mostrarTicket(t);
//                cout << "     Ticket ID: " << t.getIdTicket() << endl;
//                cout << "       Descr.: " << t.getDescripcionTarea() << endl;
//                cout << "       Prior.: " << t.getPrioridad() << endl;
//                cout << "       Status: " << t.getStatus() << endl;
                cout << "----------------------------------" <<endl;

                hayTicket = true;
            }
        }
    }

    if (!hayTicket) {
        clear();
        cout << "No tiene tickets asignados." << endl;
        pause();
        return;
    }

    cout << "=====================================" << endl;
    cout << "Seleccione el ticket a finalizar." << endl;

    int idProyecto, idSprint, idTicket;
    cout << "ID Proyecto : ";
    cin >> idProyecto;

    cout << "ID Sprint   : ";
    cin >> idSprint;

    cout << "ID Ticket   : ";
    cin >> idTicket;

    // 4) Finalizar ticket
    TicketManager tm;
    tm.finalizarTicketUsuario(idUsuario);

    pause();
}
