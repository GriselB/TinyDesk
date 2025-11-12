//
//  MenuAdmin.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#include <iostream>
#include "MenuAdmin.h"
#include "utils.h"

using namespace std;

MenuAdmin::MenuAdmin() {
    _cantidadOpciones = 4;
}

void MenuAdmin::run() {
    int opcion;
    do {
        clear();
        opcion = seleccionarOpcion();
        clear();
        ejecutarOpcion(opcion);
    } while (opcion != 0);
}

void MenuAdmin::mostrarOpciones() {
    cout << "           --- MENU ADMINISTRADOR ---" << endl;
    cout << "1- CREAR" << endl;
    cout << "2- MODIFICAR" << endl;
    cout << "3- LISTADOS" << endl;
    cout << "4- REPORTES" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
}

int MenuAdmin::seleccionarOpcion() {
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

void MenuAdmin::ejecutarOpcion(int opcion) {
    switch (opcion) {
        case 1:
            menuCrear();
            break;

        case 2:
            menuModificar();
            break;

        case 3:
            menuListados();
            break;

        case 4:
            menuReportes();
            break;

        case 0:
            cout << "Cerrando sesión.." << endl;
            SesionArchivo sesArch;
            sesArch.cerrarSesion();
            pause();
            break;
    }
}

void MenuAdmin::menuCrear() {

    CreacionAdminMenu creacionMenu;
    creacionMenu.run("CREACION");
    pause();

}

void MenuAdmin::menuModificar() {
    ModificacionAdminMenu modificacionMenu;
    modificacionMenu.run("MODIFICAR");
    pause();
}

void MenuAdmin::menuListados() {
    ListadoAdminMenu listadoMenu;
    listadoMenu.run("LISTADO");
}

void MenuAdmin::menuReportes() {
    ReportesAdminMenu reportesAdminMenu;
    reportesAdminMenu.run("REPORTES");
}
