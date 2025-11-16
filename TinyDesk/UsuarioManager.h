//
//  UsuarioManager.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#pragma once
#include <string>
#include "UsuarioArchivo.h"
#include "ArchivoRol.h"
#include "SesionArchivo.h"
#include "utils.h"

class UsuarioManager {
public:
    UsuarioManager();

    void crearUsuario();
    void mostrarUsuarios();
    int iniciarSesion();
    void eliminarUsuario();
//    bool verificarUsuarioArea(int usuarioId, int area);
    bool existeUsuario(int usuarioId);
    void cargarUsuario(Usuario &user);
    void mostrarUsuario(Usuario &usuario);
    

private:
    UsuarioArchivo _repo;
    ArchivoRol _rolRepo;

    bool existeEmail(std::string email);
};
