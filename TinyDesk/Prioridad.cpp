#include <iostream>
#include <string>
#include "Prioridad.h"

using namespace std;

Prioridad::Prioridad()
{
    _idPrioridad = 0;
}

int Prioridad::getIdPrioridad()
{
    return _idPrioridad;
}

std::string Prioridad::getDescripcionPrioridad(int n)
{
    static const char* DESCRIPCIONES[3] = { "Baja", "Media", "Alta" };

    if (n < 0 || n > 2) {
        return "Invalidas";
    }
    return DESCRIPCIONES[n];
}

void Prioridad::setIdPrioridad(int idPrioridad)
{
    if (idPrioridad < 0 || idPrioridad > 2) {
        idPrioridad = 0;
    }
    _idPrioridad = idPrioridad;
}

void Prioridad::mostrar()
{
    cout << "Prioridad: " << getDescripcionPrioridad(_idPrioridad) << "\n";
}

void Prioridad::seleccionarPrioridad()
{
    int opcion;
    do {
        cout << "--- Seleccione la Prioridad ---" << endl;
        cout << "--- 1 - Baja, 2 - Media, 3 - Alta  ---" << endl;
        cout << "Opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 3);

    setIdPrioridad(opcion - 1);
}
