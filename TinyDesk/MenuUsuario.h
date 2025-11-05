//
//  MenuUsuario.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#pragma once
#include "SesionArchivo.h"
#include "TareasUsuarioManager.h"

class MenuUsuario {
private:
    int _cantidadOpciones;

    void mostrarOpciones();
    int seleccionarOpcion();
    void ejecutarOpcion(int opcion);

    void tareas();
    void finalizarTicket();
    void reportes();

public:
    MenuUsuario();
    void run();
};
