#include <iostream>
#include <cstring>
#include "Estado.h"

using namespace std;

int Estado::getIdEstado()
{
    return _idEstado;
}
std::string Estado::getNombre()
{
    return _nombre;
}

void Estado::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}
void Estado::setNombre(std::string nombre)
{
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}
void Estado::mostrar()
{
    cout<<"Id del Estado: "<<_idEstado<<endl;
    cout<<"Nombre del Estado: "<<_nombre<<endl;
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
