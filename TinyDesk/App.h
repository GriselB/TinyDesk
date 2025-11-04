#pragma once
#include "UsuarioManager.h"
#include "MenuAdmin.h"
#include "MenuUsuario.h"

class App
{
  public:
    App();
    void run();

  protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

    UsuarioManager _usuarioManager;
    
  private:
    int _cantidadOpciones;
};

