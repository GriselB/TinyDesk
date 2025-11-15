//
//  MenuUsuario.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#include <iostream>
#include "MenuUsuario.h"
#include "utils.h"

using namespace std;

MenuUsuario::MenuUsuario() {
    _cantidadOpciones = 3;
}

void MenuUsuario::run() {
    int opcion;
    do {
        clear();
        opcion = seleccionarOpcion();
        clear();
        ejecutarOpcion(opcion);
    } while (opcion != 0);
}

void MenuUsuario::mostrarOpciones() {
    cout << "           --- MENU USUARIO ---" << endl;
    cout<<endl;
    cout << "1 - LISTAR TAREAS" << endl;
    cout << "2 - MODIFICAR TICKET" << endl;
    cout << "3 - REPORTES" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
}

int MenuUsuario::seleccionarOpcion() {
    int opcion;
    mostrarOpciones();
    cout << "---------------" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    while (opcion < 0 || opcion > _cantidadOpciones) {
        cout << "Opcion incorrecta..." << endl;
        cout << "Opcion: ";
        cin >> opcion;
    }
    return opcion;
}

void MenuUsuario::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            tareas();
            break;

        case 2:
            finalizarTicket();
            break;

        case 3:
            reportes();

        case 0:
            cout << "Cerrando Sesión..." << endl;
            SesionArchivo sesArch;
            sesArch.cerrarSesion();
            pause();
            break;
    }
}

void MenuUsuario::tareas(){
    clear();
    TareasUsuarioManager tareaUM;
    tareaUM.listarTareasUsuario();
}

void MenuUsuario::finalizarTicket(){
    clear();
    TareasUsuarioManager tareaUM;
    tareaUM.finalizarTicket();
}

void MenuUsuario::reportes(){
    clear();
    ReportesUsuarioMenu reportesUsuarioMenu;
    reportesUsuarioMenu.run("Reportes de Usuario");
}

