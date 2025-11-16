#include <cstring>
#include <iostream>
#include "Proyecto.h"
#include "Fecha.h"
#include "Estado.h"
#include "utils.h"

using namespace std;

int Proyecto::getIdProyecto()
{
    return _idProyecto;
}

string Proyecto::getNombre()
{
    return _nombre;
}

string Proyecto::getDescripcion()
{
    return _descripcion;
}


Fecha Proyecto::getFechaInicio()
{
    return _fechaInicio;
}


Fecha Proyecto::getFechaFin()
{
    return _fechaFin;
}


Fecha Proyecto::getFechaFinalizada()
{
    return _fechaFinalizada;
}


int Proyecto::getIdEstado()
{
    return _idEstado;
}

void Proyecto::setIdProyecto(int idProyecto)
{
    _idProyecto=idProyecto;
}

void Proyecto::setNombre(string nombre)
{
    strncpy(_nombre, nombre.c_str(), 49);
    _nombre[49] = '\0';
}

void Proyecto::setDescripcion(string descripcion)
{
    strncpy(_descripcion, descripcion.c_str(), 249);
    _descripcion[249] = '\0';
}

void Proyecto::setFechaInicio()
{
    _fechaInicio = Fecha("inicio");
}

void Proyecto::setFechaFin()
{
    _fechaFin = Fecha("fin");
}

void Proyecto::setFechaFinalizada()
{
    _fechaFinalizada = Fecha("finalizacion");
}

void Proyecto::setIdEstado(int idEstado)
{
    _idEstado=idEstado;
}

void Proyecto::cargar()
{
    string nombre, descripcion;
    Fecha inicio,fin,finalizada;
    cout << "Ingrese un nombre de proyecto: ";
    cin.ignore();
    getline(cin, nombre);
    setNombre(nombre);
    cout << "Ingrese una descripcion del proyecto: ";
    getline(cin, descripcion);
    setDescripcion(descripcion);
    setFechaInicio();
    setFechaFin();
    while(!fechaMenorOIgual(_fechaInicio,_fechaFin))
    {
        cout<<"Fecha de Fin anterior a Fecha de Inicio"<<endl;
        cout<<"Ingrese una fecha valida"<<endl;
        setFechaInicio();
        setFechaFin();
    }
    setIdEstado(1);
}
void Proyecto::mostrar()
{
    Estado estado;
    cout<<"Nombre del proyecto: "<<getNombre()<<endl;
    cout<<"Id del proyecto: "<<getIdProyecto()<<endl;
    cout<<"Descripción del proyecto: "<<getDescripcion()<<endl;
    cout<<"Fecha de inicio del proyecto: "<<getFechaInicio().toString()<<endl;
    cout<<"Fecha de fin del proyecto: "<<getFechaFin().toString()<<endl;
    if(getIdEstado()==2)
        cout<<"Fecha de finalización del proyecto: "<<getFechaFinalizada().toString()<<endl;
    cout<<"Estado del proyecto: "<<estado.getNombreEstado(getIdEstado())<<endl;
    cout<<"--------------------------------"<<endl;
}
