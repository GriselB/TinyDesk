#pragma once
#include <string>

class Prioridad
{
public:
    Prioridad();

    int getIdPrioridad();
    std::string getDescripcionPrioridad(int n);
    void setIdPrioridad(int idPrioridad);
    void mostrar();
    void seleccionarPrioridad();

private:
    int _idPrioridad;
};

