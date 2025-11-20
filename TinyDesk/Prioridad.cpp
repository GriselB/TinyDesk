#include <iostream>
#include <cstring>
#include "Prioridad.h"

using namespace std;

int Prioridad::getIdPrioridad()
{
    return _idPrioridad;
}

std::string Prioridad::getDescripcionPrioridad(int n)
{
    return _descripcion[n];
}

void Prioridad::setIdPrioridad(int idPrioridad)
{
    _idPrioridad=idPrioridad;
}

void Prioridad::mostrar()
{
    cout<<"ID Prioridad: "<<_idPrioridad<<endl;
    cout<<"DESCRIPCIÓN: "<<_descripcion[_idPrioridad]<<endl;
}
void Prioridad::seleccionarPrioridad()
{
    int opcion;
    do{
        cout<<"--- Seleccione la Prioridad ---"<<endl;
        cout<<"--- 1 - Baja, 2 - Media, 3 - Alta  ---"<<endl;
        cin>>opcion;
    }while(opcion<1 && opcion >3);
    setIdPrioridad(opcion-1);
}
