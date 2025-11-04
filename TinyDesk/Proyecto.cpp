#include <cstring>
#include <iostream>
#include "Proyecto.h"
#include "Fecha.h"
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

string Proyecto::getFechaInicio()
{
    return _fechaInicio.toString();
}

string Proyecto::getFechaFin()
{
    return _fechaFin.toString();
}

string Proyecto::getFechaFinalizada()
{
    return _fechaFinalizada.toString();
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
    cout<<"Ingrese un nombre de proyecto: ";
    cin>>nombre;
    setNombre(nombre);
    cout<<"Ingrese una descripcion del proyecto: ";
    setDescripcion(descripcion);
    cin>>descripcion;
    setFechaInicio();
    setFechaFin();
    setIdEstado(2);
}
void Proyecto::mostrar()
{
    string vecEstado[3]={"No Disponible","Disponible","Finalizado"};
    std::cout<<"Id del proyecto: "<<getIdProyecto()<<std::endl;
    std::cout<<"Nombre del proyecto: "<<getNombre()<<std::endl;
    std::cout<<"Descripción del proyecto: "<<getDescripcion()<<std::endl;
    std::cout<<"Fecha de inicio del proyecto: "<<getFechaInicio()<<std::endl;
    std::cout<<"Fecha de fin del proyecto: "<<getFechaFin()<<std::endl;
    std::cout<<"Fecha de finalización del proyecto: "<<getFechaFinalizada()<<std::endl;
    std::cout<<"Id del estado del proyecto: "<<vecEstado[getIdEstado()-1]<<std::endl;
}
