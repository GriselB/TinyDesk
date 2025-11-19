//
//  ListadoAdminManager.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#include <iostream>
#include "ListadoAdminManager.h"
using namespace std;

void ListadoAdminManager::listarProyectos() {
    clear();
        ProyectoManager pM;
    //cout << "----- PROYECTOS -----" << endl;
    cout << endl;
        pM.listarProyectos();
        clear();
}

void ListadoAdminManager::listarSprintsPorProyectos() {
    clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    SprintManager sprintMng;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();

    cout << "                       ----- SPRINTS POR PROYECTO -----" << endl;
    cout << endl;


    if (cantProyectos <= 0) {
        cout << "No hay proyectos registrados." << endl;
        pause();
        return;
    }

    if(cantSprints<=0){
        cout << "No hay sprint registrados." << endl;
        pause();
        return;
    }

    for (int i = 0; i < cantProyectos; i++) {
        Proyecto proyecto = archivoProyecto.leer(i);
        cout << "       Proyecto " << proyecto.getIdProyecto() << ": " << proyecto.getNombre() << endl;

        bool tieneSprint = false;

        for (int j = 0; j < cantSprints; j++) {
            //int pos = archivoSprint.buscarID(j, i);
            Sprint sprint = archivoSprint.leer(j);

            if (sprint.getIdProyecto() == proyecto.getIdProyecto()) {
                sprintMng.mostrar(j, true);
                cout << "-------------------------------" << endl;
                tieneSprint = true;
            }

        }
        if (!tieneSprint) cout << "   -- No tiene sprints asignados --" << endl;
        cout << "-------------------------" << endl;
    }

    pause();
}


void ListadoAdminManager::listarTicketsPorSprints() {
    clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    TicketArchivo archivoTicket;
    UsuarioArchivo archivoUsuario;

    int cantProy = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();
    int cantTickets = archivoTicket.getCantidadRegistros();
    int cantUsuarios = archivoUsuario.getCantidadRegistros();

    cout << "----- TICKETS POR PROYECTO Y SPRINT -----" << endl;

    if (cantProy <= 0) {
        cout << "No hay proyectos registrados aun." << endl;
        pause();
        return;
    }
    if (cantSprints <= 0) {
        cout << "No hay sprints registrados aun." << endl;
        pause();
        return;
    }
    if (cantTickets <= 0) {
        cout << "No hay tickets registrados aun." << endl;
        pause();
        return;
    }

    for (int i = 0; i < cantProy; i++) {
        Proyecto proyecto = archivoProyecto.leer(i);
        if(proyecto.getIdProyecto() == -1) continue;
        
        cout << "Proyecto " << proyecto.getIdProyecto() << ": " << proyecto.getNombre() << endl;

        bool tieneSprint = false;

        for (int j = 0; j < cantSprints; j++) {
            int pos = archivoSprint.buscarID(j, i);
            Sprint sprint = archivoSprint.leer(pos);
            if(sprint.getIdSprint() == -1) continue;
            if (sprint.getIdProyecto() != proyecto.getIdProyecto()) continue;

            tieneSprint = true;
            cout << "   Sprint " << sprint.getNombre() << endl;

            bool tieneTickets = false;

            for (int k = 0; k < cantTickets; k++) {
                Ticket ticket;
                int pos = archivoTicket.buscarIDTicketSprintProyecto(k, i, j);
                if(pos < 0) return;
                if(!archivoTicket.leer(pos, ticket)) continue;
                if(ticket.getIdProyecto() != proyecto.getIdProyecto()) continue;
                if(ticket.getIdSprint() != sprint.getIdSprint()) continue;

                tieneTickets = true;


                string usuarioAsignado = "-- sin usuario asignado --";
                string apellidoUsuarioAsignado = "";
                int idEmpleado = ticket.getIdEmpleado();

                for (int u = 0; u < cantUsuarios; u++) {
                    Usuario user = archivoUsuario.leer(u);
                    if (user.getIdUsuario() == idEmpleado) {
                        usuarioAsignado = user.getNombre();
                        apellidoUsuarioAsignado = user.getApellido();
                        break;
                    }
                }

                cout << "      • Ticket " << ticket.getIdTicket() << endl;
                cout << "        Asignado a: " << usuarioAsignado << apellidoUsuarioAsignado << endl;
                cout << "        Descripcion: " << ticket.getDescripcionTarea() << endl;
                cout << "        Prioridad: " << ticket.getPrioridad() << endl;
                cout << "        Fecha inicio: " << ticket.getFechaInicio().toString() << endl;
                cout << "        Fecha a finalizar: " << ticket.getFechaFin().toString() << endl;
                if (ticket.getFechaFinalizada().getAnio()!=0) {
                    cout<<"        Fecha finalizada: " << ticket.getFechaFinalizada().toString()<<endl;
                } else {
                    cout << "        Status: " << ticket.getStatus() << endl;

                }
                cout << "--------------------------------" << endl;
            }
            if (!tieneTickets) cout << "      -- No tiene tickets --" << endl;
        }

        if (!tieneSprint) cout << "   -- No tiene sprints asignados --" << endl;

        cout << "------------------------------------------------------------" << endl;
        cout << "------------------------------------------------------------" << endl;

    }

    pause();
}

void ListadoAdminManager::listarUsuarios(){
    clear();
    UsuarioManager userManager;
    userManager.mostrarUsuarios();
    pause();
}

