#pragma once
#include <iostream>
#include "ReportesAdminMenuManager.h"

using namespace std;

void ReportesAdminMenuManager::estadisticasDetalladasDeUnUsuario(){
    clear();

    UsuarioArchivo usuarioRepo;
    TicketArchivo  ticketRepo;
    SprintArchivo  sprintRepo;

    int cantUsuarios = usuarioRepo.getCantidadRegistros();
    if (cantUsuarios < 1) {
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

    cout << "=========== SELECCION DE USUARIO ===========" << endl;
    for (int i = 0; i < cantUsuarios; i++) {
        Usuario u = usuarioRepo.leer(i);
        if ( !u.getActivo() ) continue;
        if (u.getIdRol() == 1) continue;

        cout << "ID: " << u.getIdUsuario() << endl;
        cout << " | Nombre: " << u.getNombre() << " " << u.getApellido() << endl;
        cout << " | Area: " << u.getArea().getNombreArea() << endl;
    }
    cout << "---------------------------------------------" << endl;
    cout << "---------------------------------------------" << endl;

    int idUsuarioSel;
    cout << "Ingrese el ID de usuario para ver sus estadisticas: ";
    cin >> idUsuarioSel;

    int posUsuario = usuarioRepo.buscarID(idUsuarioSel);
    if (posUsuario < 0) {
        cout << "No existe un usuario con ese ID." << endl;
        pause();
        return;
    }

    Usuario userSelected = usuarioRepo.leer(posUsuario);
    if(userSelected.getIdUsuario() == -1){
        cout << "El usuario seleccionado no existe." << endl;
        pause();
        return;
    }
    if ( !userSelected.getActivo() ) {
        cout << "El usuario seleccionado esta dado de baja." << endl;
        pause();
        return;
    }
    if (userSelected.getIdRol() == 1) {
        cout << "El usuario seleccionado es administrador. Este reporte es solo para empleados." << endl;
        pause();
        return;
    }
    clear();

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
    int totalUser = 0;
    int finalizadosUser = 0;
    int finalizadosATiempoUser = 0;
    float mediaUser = 0.0;
    double porcentajeUser = 0.0;
    double cvUser = 0.0;
    float mediaUserATiempo = 0.0;
    double porcentajeUserATiempo = 0.0;
    double cvUserATiempo = 0.0;

    int idArea = userSelected.getArea().getIdArea();
    string nombreAreaUsuario = userSelected.getArea().getNombreArea();

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
        if ( t.getIdEmpleado() != userSelected.getIdUsuario() ) continue;
        totalUser++;
        if (esFinalizado) {
            finalizadosUser++;
            if (esFinalizadoATiempo) {
                finalizadosATiempoUser++;
            }
        }

    }

    clear();
    cout << "               =========== REPORTE DETALLADO DE USUARIO ===========" << endl;
    cout << "Usuario: " << userSelected.getNombre() << " " << userSelected.getApellido() << endl;
    cout << "ID: " << userSelected.getIdUsuario() << endl;
    cout << "Area: " << nombreAreaUsuario << endl;
    cout << "-------------------------" << endl << endl;

    // estadisticas del usuario
    if (totalUser == 0) {
        cout << "El usuario no tiene tickets asignados." << endl;
        delete [] vecTickets;
        delete [] vecSprints;
        pause();
        return;
    } else if (finalizadosUser == 0) {
        cout << "El usuario no finalizo ningun ticket (todos pendientes)." << endl;
        delete [] vecTickets;
        delete [] vecSprints;
        pause();
        return;
    } else {
        // cumplimiento user
        mediaUser = finalizadosUser / float(totalUser);
        porcentajeUser = round(mediaUser * 10000.0) / 100.0;
        double varUsr = totalUser * mediaUser * (1 - mediaUser);
        double desvioUsr = sqrt(varUsr);
        cvUser = (desvioUsr / finalizadosUser) * 100.0;

        cout << "    ---> ESTADISTICAS DEL USUARIO" << endl;
        cout << "           --------------------------" << endl;
        cout << "Total tickets asignados al usuario: " << totalUser << endl;
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

            compararRendimientoUsuario( "AREA " + nombreAreaUsuario,
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

void ReportesAdminMenuManager::ticketsSinTerminar(){
cout<<"ticketsSinTerminar"<<endl;
pause();
}

void ReportesAdminMenuManager::sprintsCompletadosPorProyecto(){

 clear();

    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    SprintManager sprint;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints = archivoSprint.getCantidadRegistros();

    cout << "            ----- SPRINTS COMPLETADOS POR PROYECTO -----" << endl;

    if (cantProyectos <= 0) {
        cout << "No hay proyectos registrados."<< endl;
        pause();
        return;
    }

    if (cantSprints <= 0) {
        cout << "No hay sprints registrados."<< endl;
        pause();
        return;
    }

    int *idsProyecto = new int[cantProyectos];
    int *totalSprints = new int[cantSprints]{0};
    int *finalizados = new int[cantSprints]{0};
    int *bajas = new int[cantSprints]{0};
    int *abiertos = new int[cantSprints]{0};


    for (int i = 0; i < cantProyectos; i++) {
        Proyecto p = archivoProyecto.leer(i);
        idsProyecto[i] = p.getIdProyecto();
    }


    for (int j = 0; j < cantSprints; j++) {
        Sprint s = archivoSprint.leer(j);

        for (int i = 0; i < cantProyectos; i++) {
            if (idsProyecto[i] == s.getIdProyecto()) {

                totalSprints[i]++;
                if (s.getIdEstado() == 0) {
                    bajas[i]++;
                }
                if (s.getIdEstado() == 1) {
                    abiertos[i]++;
                }

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
        cout << "  Abiertos:          " << abiertos[i] << endl;
        cout << "  Finalizados:       " << finalizados[i] << endl;
        cout << "  Bajas:             " << bajas[i] << endl;
        cout << "  Progreso:          " << porcentaje << "% " << sprint.dibujarBarra(porcentaje) << endl;
        cout << "------------------------------------------"<< endl;
    }


    delete[] idsProyecto;
    delete[] totalSprints;
    delete[] finalizados;
    delete[] abiertos;
    delete[] bajas;
    pause();
}
void ReportesAdminMenuManager::sprintsAtrasadosArea(){

    clear();
    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    SprintManager sprintMgm;
    ProyectoManager  proyecto;
    Proyecto proy;
    Area area;


    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints   = archivoSprint.getCantidadRegistros();

    if (cantProyectos == 0 || cantSprints == 0) {
        cout << "No hay datos para generar el reporte." << endl;
        pause();
        return;
    }

    cout << "===== REPORTE DE ATRASOS POR AREA =====" << endl;

    int idProyecto, posProyecto;

    proyecto.listarProyectosNombreID();
    cout << "Ingrese el ID del proyecto para generar el reporte: ";
    cin >> idProyecto;

    posProyecto = proyecto.buscarID(idProyecto);
    proy = archivoProyecto.leer(posProyecto);
    cout << "Proyecto: " << proy.getNombre() << endl;


    int *areas = new int[cantSprints];
    int cantAreas = 0;

    for (int i = 0; i < cantSprints; i++) {
        Sprint sprint = archivoSprint.leer(i);

        if (sprint.getIdProyecto() != idProyecto) continue;

        int idArea = sprint.getArea().getIdArea();
        bool existe = false;

        for (int a = 0; a < cantAreas; a++) {
            if (areas[a] == idArea) {
                existe = true;
                break;
            }
        }

        if (!existe) {
            areas[cantAreas++] = idArea;
        }
    }

    if (cantAreas == 0) {
        cout << "Este proyecto no tiene sprints asignados." << endl;
        delete[] areas;
        pause();
        return;
    }


    int *totalPorArea     = new int[cantAreas] {0};
    int *atrasadosPorArea = new int[cantAreas] {0};
    int *diasAtrasoAcum   = new int[cantAreas] {0};



    for (int i = 0; i < cantSprints; i++) {
        Sprint sprint = archivoSprint.leer(i);

        if (sprint.getIdProyecto() != idProyecto) continue;

        int idArea = sprint.getArea().getIdArea();

        int index = -1;
        for (int a = 0; a < cantAreas; a++) {
            if (areas[a] == idArea) {
                index = a;
                break;
            }
        }

        if (index == -1) continue;

        totalPorArea[index]++;

        if (sprint.getFinalizoTarde()) {
            atrasadosPorArea[index]++;
            //diasAtrasoAcum[index] += sprint.getDiasAtraso();
        }
    }


    for (int i = 0; i < cantAreas; i++) {
        cout << "----------------------------"<< endl;
        cout << "Area: " << area.buscarNombrePorID(areas[i])  << endl;
        cout << "  - Total de sprints: " << totalPorArea[i] << endl;
        cout << "  - Finalizados tarde: " << atrasadosPorArea[i] << endl;

        if (totalPorArea[i] == 0) {
            cout << "  - % atraso: 0%" << endl;
            continue;
        }

        float porc = (atrasadosPorArea[i] * 100.0f) / totalPorArea[i];

        cout << "  - % atraso: " << porc << endl;

//        if (atrasadosPorArea[i] > 0) {
//            float promedio = diasAtrasoAcum[i] / (float)atrasadosPorArea[i];
//            cout << "  - Promedio de atraso: " << promedio << " dias" <<endl;
//        }
        cout << "----------------------------"<< endl;
    }

    delete[] areas;
    delete[] totalPorArea;
    delete[] atrasadosPorArea;
    delete[] diasAtrasoAcum;

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

void ReportesAdminMenuManager::proyectosSinSprintAsignados()
{
    clear();
    int total;
    float disponibles,noDisponibles, disponiblesSinAsignar;
    disponibles = 0;
    noDisponibles = 0;
    disponiblesSinAsignar = 0;
    Sprint sprint;
    ProyectoArchivo proyectoArchivo;
    SprintArchivo sprintArchivo;
    int cant = proyectoArchivo.getCantidadRegistros();
    for(int h = 0; h < cant;h++)
    {
        if(proyectoArchivo.leer(h).getIdEstado()==1)
            disponibles++;
        else
            noDisponibles++;
    }
    int* vec = new int[cant]{};
    int cantSprints = sprintArchivo.getCantidadRegistros();
    for(int i=0;i<cantSprints;i++)
    {
        int num = sprintArchivo.leer(i).getIdProyecto();
        vec[num-1]++;
    }
        for(int j = 0;j<cant;j++)
    {
        if(vec[j]==0)
            disponiblesSinAsignar++;
    }
    if(disponibles!=0)
    {
        total= ((disponiblesSinAsignar-noDisponibles)/disponibles)*100;
        cout<<"El porcentaje de proyectos disponibles sin sprint asignados es de: "<< total<<"%"<<endl;
    }
    else
        cout<<"El porcentaje de proyectos disponibles sin sprint asignados es de: 0%"<<endl;
    delete[] vec;
    pause();
}
