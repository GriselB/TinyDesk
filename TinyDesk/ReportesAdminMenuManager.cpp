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
    
    int idArea = userSelected.getArea().getIdArea();
    string nombreAreaUsuario = userSelected.getArea().getNombreArea();
    
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
        if ( ticket.getIdEmpleado() != userSelected.getIdUsuario() ) continue;
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

void ReportesAdminMenuManager::sprintsAtrasadosArea() {
    clear();
    
    ProyectoArchivo archivoProyecto;
    SprintArchivo archivoSprint;
    ProyectoManager managerProyecto; 
    Area areaRepo; 
    Proyecto proy;

    int cantProyectos = archivoProyecto.getCantidadRegistros();
    int cantSprints   = archivoSprint.getCantidadRegistros();


    if (cantProyectos == 0 || cantSprints == 0) {
        cout << "No hay datos suficientes para generar el reporte." << endl;
        pause();
        return;
    }

    cout << "===== REPORTE DE ATRASOS POR AREA =====" << endl;

    managerProyecto.listarProyectosNombreID();
    
    int idProyecto;
    cout << "Ingrese el ID del proyecto: ";
    cin >> idProyecto;
    
    int posProyecto = managerProyecto.buscarID(idProyecto);
    if (posProyecto == -1) {
        cout << "ID de proyecto no valido." << endl;
        pause();
        return;
    }
    
    proy = archivoProyecto.leer(posProyecto);
    
    clear();
    cout << "===== REPORTE DE ATRASOS: " << proy.getNombre() << " =====" << endl;

    int *areasIds = new int[cantSprints]; 
    int *totalSprintsArea = new int[cantSprints] {0};
    int *totalAtrasadosArea = new int[cantSprints] {0};
    int *diasAtrasoAcumulados = new int[cantSprints] {0};
    
    int contAreasEncontradas = 0;

    for (int i = 0; i < cantSprints; i++) {
        Sprint sprint = archivoSprint.leer(i);


        if (sprint.getIdProyecto() != idProyecto) continue;


        if (sprint.getIdEstado() != 2) continue; 

        int idAreaActual = sprint.getArea().getIdArea();

        // Revisamos si ya existe el area
        int indexArea = -1;
        for (int k = 0; k < contAreasEncontradas; k++) {
            if (areasIds[k] == idAreaActual) {
                indexArea = k;
                break;
            }
        }

        // Si es un area nueva, la agregamos
        if (indexArea == -1) {
            indexArea = contAreasEncontradas;
            areasIds[indexArea] = idAreaActual;
            contAreasEncontradas++;
        }

        totalSprintsArea[indexArea]++;


        Fecha fechaPactada = sprint.getFechaFin();

        Fecha fechaReal = sprint.getFechaFinalizada(); 

        int diasDiferencia = fechaPactada.diferenciaEnDias(fechaReal);

        if (diasDiferencia > 0) {
            totalAtrasadosArea[indexArea]++;
            diasAtrasoAcumulados[indexArea] += diasDiferencia;
        }
    }


    if (contAreasEncontradas == 0) {
        cout << "El proyecto no tiene sprints finalizados o asignados." << endl;
    } else {
        for (int i = 0; i < contAreasEncontradas; i++) {
            cout << "--------------------------------------------" << endl;

            cout << "AREA: " << areaRepo.buscarNombrePorID(areasIds[i]) << endl;
            
            cout << "  Sprints Analizados:    " << totalSprintsArea[i] << endl;
            cout << "  Sprints Atrasados:     " << totalAtrasadosArea[i] << endl;

            if (totalSprintsArea[i] > 0) {
                float porcentaje = (totalAtrasadosArea[i] * 100.0f) / totalSprintsArea[i];
                cout << "  % de Impuntualidad:    " << porcentaje << "%" << endl;

                if (totalAtrasadosArea[i] > 0) {
                    float promedio = (float)diasAtrasoAcumulados[i] / totalAtrasadosArea[i];
                    cout << "  Promedio de demora:    " << promedio << " dias" << endl;
                } else {
                    cout << "  Promedio de demora:    0 dias (Excelente)" << endl;
                }
            }
            cout << "--------------------------------------------" << endl;
        }
    }
    delete[] areasIds;
    delete[] totalSprintsArea;
    delete[] totalAtrasadosArea;
    delete[] diasAtrasoAcumulados;

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
    cout<<" ------------ PROYECTOS COMPLETADOS ------------ "<<endl<<endl;
    cout<<"La cantidad de Proyectos completados es del: "<<resultado<<"%"<<endl<<endl;
    cout<<"La cantidad de Proyectos no completados es del: "<<100-resultado<<"%"<<endl<<endl;
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
    cout<<" ------------ PROYECTOS FINALIZADOS A TIEMPO ------------ "<<endl<<endl;
    cout<<"El porcentaje de Proyectos finalizados a tiempo es de: "<<resultado<<"%"<<endl<<endl;
    cout<<"El porcentaje de Proyectos finalizados fuera de tiempo es de: "<<100-resultado<<"%"<<endl<<endl;
    pause();
}

void ReportesAdminMenuManager::proyectosSinSprintAsignados()
{
    clear();
    int total,cantProyectos, *vec;
    float disponibles, disponiblesSinAsignar;
    disponibles = 0;
    disponiblesSinAsignar = 0;
    Sprint sprint;
    ProyectoArchivo proyectoArchivo;
    SprintArchivo sprintArchivo;
    cantProyectos = proyectoArchivo.getCantidadRegistros();
    vec = new int[cantProyectos]{};
    int cantSprints = sprintArchivo.getCantidadRegistros();
    for(int i=0;i<cantSprints;i++)
    {
        int num = sprintArchivo.leer(i).getIdProyecto();
        if(num > 0 && num <= cantProyectos)
            vec[num-1]++;
    }

    for(int h = 0; h < cantProyectos;h++)
    {
        if(proyectoArchivo.leer(h).getIdEstado()==1)
            disponibles++;
        else
            vec[h]=-1;
    }
    for(int j = 0;j<cantProyectos;j++)
    {
        if(vec[j]==0)
            disponiblesSinAsignar++;
    }
    cout<<"-------------- PROYECTOS DISPONIBLES SIN SPRINTS ASIGNADOS --------------"<<endl<<endl;
    if(disponibles!=0)
    {
        total= (disponiblesSinAsignar/disponibles)*100;
        cout<<"El porcentaje de Proyectos disponibles sin Sprint asignados es de: "<< total<<"%"<<endl<<endl;
        if(total>0)
        {
            cout<<"¿Desea ver la lista de Proyectos disponibles sin Sprints asignados?  s/n"<<endl<<endl;
            char opcion;
            cin>>opcion;
            if(opcion == 's')
            {
               for(int x = 0;x<cantProyectos;x++)
                {
                    if(vec[x]==0)
                    {
                        proyectoArchivo.leer(x).mostrar();
                    }
                }
            }
        }
    }
    else
        cout<<"El porcentaje de Proyectos disponibles sin Sprint asignados es de: 0%"<<endl<<endl;
    delete[] vec;
    pause();
}

void ReportesAdminMenuManager::progresoTicketsPorProyecto() {

    clear();

    ProyectoArchivo proyectoRepo;
    TicketArchivo   ticketRepo;

    int cantProyectos = proyectoRepo.getCantidadRegistros();
    int cantTickets   = ticketRepo.getCantidadRegistros();

    cout << "------ PROGRESO DE TICKETS POR PROYECTO ------" << endl << endl;

    if (cantProyectos <= 0) {
        cout << "No hay proyectos registrados." << endl;
        pause();
        return;
    }

    if (cantTickets <= 0) {
        cout << "No hay tickets registrados." << endl;
        pause();
        return;
    }

    int *idsProyecto   = new int[cantProyectos];
    int *totalTickets  = new int[cantProyectos]{0};
    int *disp          = new int[cantProyectos]{0};
    int *noDisp        = new int[cantProyectos]{0};
    int *finalizados   = new int[cantProyectos]{0};

    for (int i = 0; i < cantProyectos; i++) {
        Proyecto p = proyectoRepo.leer(i);
        idsProyecto[i] = p.getIdProyecto();
    }

    for (int j = 0; j < cantTickets; j++) {
        Ticket t;
        ticketRepo.leer(j, t);

        int idP = t.getIdProyecto();
        int idx = -1;

        for (int i = 0; i < cantProyectos; i++) {
            if (idsProyecto[i] == idP) {
                idx = i;
                break;
            }
        }
        if (idx == -1) continue;

        totalTickets[idx]++;

        int idEstado = t.getStatus().getIdEstado();

        if (idEstado == 0)      noDisp[idx]++;
        else if (idEstado == 1) disp[idx]++;
        else if (idEstado == 2) finalizados[idx]++;
    }

    SprintManager sprintManager;

    for (int i = 0; i < cantProyectos; i++) {

        Proyecto p = proyectoRepo.leer(i);

        cout << "Proyecto " << p.getIdProyecto()
             << " - " << p.getNombre() << endl;

        if (totalTickets[i] == 0) {
            cout << "  No tiene tickets registrados." << endl;
            cout << "------------------------------------------" << endl;
            continue;
        }

        int tot         = totalTickets[i];
        int completados = finalizados[i] + noDisp[i];
        int pendientes  = disp[i];

        float porcCompleto  = (completados * 100.0f) / tot;
        float porcPendiente = (pendientes  * 100.0f) / tot;

        cout << "  Tickets totales    : " << tot << endl;
        cout << "  Finalizados        : " << finalizados[i] << endl;
        cout << "  No disponibles     : " << noDisp[i] << endl;
        cout << "  Disponibles        : " << disp[i] << endl;
        cout << "  Progreso           : " << porcCompleto  << "% completado, "
                                         << porcPendiente << "% pendiente" << endl;
        cout << "  Barra de progreso  : "
             << sprintManager.dibujarBarra(porcCompleto) << endl;
        cout << "------------------------------------------" << endl;
    }

    delete [] idsProyecto;
    delete [] totalTickets;
    delete [] disp;
    delete [] noDisp;
    delete [] finalizados;

    pause();
}

void ReportesAdminMenuManager::rankingAreasPorPrioridad(){
    clear();
    Ticket ticket;
    Sprint sprint;
    TicketArchivo ticketArch;
    SprintArchivo sprintArch;
    int vecTotal[3][5] = {};
    int vecFinalizadas[3][5] = {};
    float porcentaje[5];

    int cantidadTickets = ticketArch.getCantidadRegistros();
    if(cantidadTickets < 1){
        cout << "No hay Tickets." << endl;
        pause();
        return;
    }
    int cantidadSprints = sprintArch.getCantidadRegistros();
    if(cantidadSprints < 1){
        cout << "No hay Tickets." << endl;
        pause();
        return;
    }

    for(int i = 0; i < cantidadTickets; i++){
        if( !ticketArch.leer(i, ticket) ) {
            cout << "Error al leer ticket." << endl;
            break;
        }
        for(int j=0; j < cantidadSprints; j++){
            sprint = sprintArch.leer(j);
            if( ticket.getIdSprint() != sprint.getIdSprint() ||
               ticket.getIdProyecto() != sprint.getIdProyecto() ) continue;

            int idPrioridad = ticket.getPrioridad().getIdPrioridad();
            int idArea = sprint.getArea().getIdArea();

            vecTotal[idPrioridad-1][idArea-1]++;

            if(ticket.getStatus().getIdEstado() == 2){
                vecFinalizadas[idPrioridad-1][idArea-1]++;
            }
        }
    }

    for(int i = 0; i < 3; i ++){
        Prioridad prioridad;
        Area area;
        int idMax = 0;
        int idMin = 0;

        for(int j = 0; j < 5; j++){
            if(vecTotal[i][j] > 0){
                porcentaje[j] = vecFinalizadas[i][j] / float(vecTotal[i][j]);
            } else {
                porcentaje[j] = -1;
            }
        }

        for(int k = 0; k < 5; k++){
            if(porcentaje[k] > porcentaje[idMax]) idMax = k;
            if(porcentaje[k] < porcentaje[idMin]) idMin = k;
        }

        cout << "   ----> PRIORIDAD: " << prioridad.getDescripcionPrioridad(i) << " <----" << endl;
        cout << endl;
        if(porcentaje[idMax] > 0){
            cout << ">> MEJOR desempe–o: " << area.buscarNombrePorID(idMax+1) << endl;
            cout << "Finalizados: " << round(porcentaje[idMax] * 10000) / 100 << "%" << endl;
        } else {
            cout << ">> MEJOR desempe–o: No Hubo" << endl;
        }
        if(porcentaje[idMin] >= 0){
        cout << "--------------------" << endl;
        cout << ">> PEOR desempe–o: " << area.buscarNombrePorID(idMin+1) << endl;
        cout << "Finalizados: " << round(porcentaje[idMin] * 10000) / 100 << "%" << endl;
        } else {
            cout << ">> PEOR desempe–o: No Hubo" << endl;
        }
        cout << "=================================" << endl;

    }
    pause();
}
