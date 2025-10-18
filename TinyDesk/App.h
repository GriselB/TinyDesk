#pragma once

class App
{
  public:
    App();
    void run();

  protected:
    void mostrarOpciones();
    int seleccionOpcion();
    void ejecutarOpcion(int opcion);

  private:
    int _cantidadOpciones;
};

