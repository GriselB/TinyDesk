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
#include "ArchivoRol.h"
#include "utils.h"

class UsuarioManager {
public:
    UsuarioManager();

    void crearUsuario();
    void mostrarUsuarios();
    int iniciarSesion();
    void eliminarUsuario();

private:
    UsuarioArchivo _repo;
    ArchivoRol _rolRepo;

    bool existeEmail(std::string email);
};

