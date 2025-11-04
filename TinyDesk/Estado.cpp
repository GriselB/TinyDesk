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
        cout<<"--- Opcion 0 - No disponible !! Opcion 1 - Disponible ||  || Opcion 2 - Finalizado  ---"<<endl;
        cin>>opcion;
        if(opcion==0)
            setIdEstado(0);
        else if(opcion==1)
            setIdEstado(1);
        else if(opcion==2)
            setIdEstado(2);
        else
            cout<<"Opcion de Estado invalida"<<endl;
    }while(opcion!=0 && opcion!=1 && opcion!=2);
}
