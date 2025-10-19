//
//  UsuarioManager.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#pragma once
#include <string>
#include "Usuario.h"
#include "UsuarioArchivo.h"

class UsuarioManager {
public:
    UsuarioManager();

    void crearUsuario();
    void mostrarUsuarios();
    void iniciarSesion();

private:
    UsuarioArchivo _repo;

    bool existeEmail(std::string email);
};

