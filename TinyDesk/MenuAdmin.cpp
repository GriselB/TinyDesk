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
            cout << "Volviendo al menu principal..." << endl;
            pause();
            break;
    }
}

void MenuAdmin::menuCrear() {
    cout << "menu crear" << endl;
    pause();

}

void MenuAdmin::menuModificar() {
    cout << "menu modificar" << endl;
    pause();
}

void MenuAdmin::menuListados() {
    ListadoAdminMenu listadoMenu;
    listadoMenu.run("Listado");
}

void MenuAdmin::menuReportes() {
    clear();
    cout << "      --- REPORTES ---" << endl;
    cout << "1- Porcentaje de Tickets completado por usuario" << endl;
    cout << "2- Porcentaje de Tickets sin terminar" << endl;
    cout << "3- Porcentaje de Sprints completados por proyecto" << endl;
    cout << "4- Porcentaje de Sprint sin terminar por proyecto" << endl;
    cout << "-----------------" << endl;
    cout << "0- Volver" << endl;
    cout << "Opcion: ";
    int opcion;
    cin >> opcion;
    cout << "Has elegido el reporte " << opcion << endl;
    pause();
}
