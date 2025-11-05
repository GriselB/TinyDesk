//
//  MenuAdmin.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 30/10/2025.
//

#pragma once
#include "ListadoAdminMenu.h"
#include "CreacionAdminMenu.h"
#include "modificacionAdminMenu.h"
#include "SesionArchivo.h"

class MenuAdmin {
private:
    int _cantidadOpciones;

    void mostrarOpciones();
    int seleccionarOpcion();
    void ejecutarOpcion(int opcion);

    // Submenús
    void menuCrear();
    void menuModificar();
    void menuListados();
    void menuReportes();

public:
    MenuAdmin();
    void run();
};
