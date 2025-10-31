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
        pM.listarProyectos();
}

void ListadoAdminManager::listarSprintsPorProyectos() {
    clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    SprintManager sprintMng;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();

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

    cout << "----- SPRINTS POR PROYECTO -----" << endl;

    for (int i = 0; i < cantProyectos; i++) {
        Proyecto proyecto = archivoProyecto.leer(i);
        cout << "       Proyecto " << proyecto.getIdProyecto() << ": " << proyecto.getNombre() << endl;

        bool tieneSprint = false;

        for (int j = 0; j < cantSprints; j++) {
            Sprint sprint = archivoSprint.leer(j);
            
            if (sprint.getIdProyecto() == proyecto.getIdProyecto()) {
                sprintMng.mostrar(j, true);
                tieneSprint = true;
            }
            
        }
        if (!tieneSprint) cout << "   -- No tiene sprints asignados --" << endl;
        cout << "---------------------------------------------" << endl;
    }

    pause();
}

/// OJO LOS COMENTADOS..   ‼️ QUITAR CUANDO SE INTEGRE TICKET ARCHIVO Y MANAGER ‼️
void ListadoAdminManager::listarTicketsPorSprints() {
    clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    //ArchivoTicket archivoTicket;
    UsuarioArchivo archivoUsuario;

    int cantProy = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();
    int cantTickets = -1;//archivoTicket.getCantidadRegistros();
    int cantUsuarios = archivoUsuario.getCantidadRegistros();

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

    cout << "----- TICKETS POR PROYECTO Y SPRINT -----" << endl;

    for (int i = 0; i < cantProy; i++) {
        Proyecto proyecto = archivoProyecto.leer(i);
        cout << "Proyecto " << proyecto.getIdProyecto() << ": " << proyecto.getNombre() << endl;

        bool tieneSprint = false;

        for (int j = 0; j < cantSprints; j++) {
            Sprint sprint = archivoSprint.leer(j);
            if (sprint.getIdProyecto() != proyecto.getIdProyecto()) continue;

            tieneSprint = true;
            cout << "   Sprint " << sprint.getIdSprint() << ": " << sprint.getNombre() << endl;

            bool tieneTickets = false;

            for (int k = 0; k < cantTickets; k++) {
                Ticket ticket ;//= archivoTicket.Leer(k);
                if (ticket.getIdSprint() != sprint.getIdSprint()) continue;

                tieneTickets = true;

                string usuarioAsignado = "-- sin usuario asignado --";
                int idEmpleado = ticket.getIdEmpleado();

                for (int u = 0; u < cantUsuarios; u++) {
                    Usuario user = archivoUsuario.leer(u);
                    if (user.getIdUsuario() == idEmpleado) {
                        usuarioAsignado = user.getNombre();
                        break;
                    }
                }

                cout << "      • Ticket " << ticket.getIdTicket()<< ": " << ticket.getDescripcionTarea() << endl;
                cout << "        Asignado a: " << usuarioAsignado << endl;
                cout << "        Descripcion: " << ticket.getDescripcionTarea() << endl;
                cout << "        Prioridad: " << ticket.getPrioridad() << endl;
                cout << "        Fecha inicio: " << ticket.getFechaInicio().toString() << endl;
                cout << "        Fecha a finalizar: " << ticket.getFechaFin().toString() << endl;
                if (!ticket.getFechaFinalizada().toString().empty()) {
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

