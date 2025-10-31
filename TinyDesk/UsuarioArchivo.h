//
//  UsuarioArchivo.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#pragma once
#include <string>
#include "Usuario.h"

class UsuarioArchivo
{
  public:
    UsuarioArchivo(std::string nombreArchivo = "usuarios.dat");

    bool guardar(Usuario registro);
    bool guardar(int pos, Usuario registro);
    int  buscarID(int idUsuario);
    bool eliminar(int pos);
    
    Usuario leer(int pos);
    int leerTodos(Usuario registros[], int cantidad);
    int getCantidadRegistros();
    int getNuevoID();

  private:
    std::string _nombreArchivo;
};
