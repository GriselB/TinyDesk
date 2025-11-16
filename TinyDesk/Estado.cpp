#include <iostream>
#include <cstring>
#include "Estado.h"

using namespace std;

int Estado::getIdEstado()
{
    return _idEstado;
}

std::string Estado::getNombreEstado(int n)
{
    return _nombres[n];
}

void Estado::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}

void Estado::mostrar()
{
    cout<<"Id del Estado: "<<_idEstado<<endl;
    cout<<"Nombre del Estado: "<<_nombres[_idEstado]<<endl;
}
void Estado::seleccionarEstado()
{
    int opcion;
    do{
        cout<<"--- Seleccione el Estado ---"<<endl;
        cout<<"--- 1 - No Disponible, 2 - Disponible, 3 - Finalizado  ---"<<endl;
        cin>>opcion;
    }while(opcion<1 && opcion >3);
    setIdEstado(opcion-1);
}
