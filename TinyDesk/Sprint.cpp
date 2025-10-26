#include <cstring>
#include <iostream>
#include "Sprint.h"
#include "Fecha.h"
#include "Proyecto.h"

using namespace std;

void Sprint::Cargar() {

    string nombreSprint;
    int idArea, idProyecto;
    Fecha fechaInicio, fechaFin;

    /*cout << "Proyecto: ";
    cin>>idProyecto;
    setProyecto(idProyecto);*/

    // Asegurate de que cargarFecha est� declarado en Sprint.h
    cargarFecha(fechaInicio, "inicio");
    setFechaInicio(fechaInicio);

    cargarFecha(fechaFin, "fin");
    setFechaFin(fechaFin);

    generarNombre();

    // luego cambiarlo por metodo cargarArea()
    do {
        cout << "ID de �rea: "<< endl;
        cout << "1: Administraci�n" << endl;
        cout << "2: Backend" << endl;
        cout << "3: Frontend" << endl;
        cout << "4: QA" << endl;
        cout << "5: UX/UI" << endl;
        cout << "ID �rea: ";
        cin >> idArea;
        setIdArea(idArea);
    } while (idArea < 1 || idArea > 5);

    setActivo(true);
}

void Sprint::Mostrar() {
    cout << "ID Sprint: " << getIdSprint() << endl;
    cout << "Nombre: "  << getNombre() << endl;

    cout << "Proyecto: " << _proyecto.getIdProyecto() << endl;

    cout << "ID �rea: " << getIdArea() << endl;

    cout << "Fecha Inicio: " << getFechaInicio().toString() << endl;
    cout << "Fecha Fin:   " << getFechaFin().toString() << endl;

    cout << "Activo: " << (getActivo() ? "S�" : "No") << endl;
}

void Sprint::generarNombre() {
    string nombre = _proyecto.getNombre() + " - Sprint " + to_string(_idSprint) +
                    " (" + _fechaInicio.toString() + " - " +
                    _fechaFin.toString() + ")";
    setNombre(nombre);
}

void Sprint::cargarFecha(Fecha &f, const string &nombre) {
    int dia, mes, anio;
    cout << "Ingrese d�a de " << nombre << ": ";
    cin >> dia;
    cout << "Ingrese mes de " << nombre << ": ";
    cin >> mes;
    cout << "Ingrese a�o de " << nombre << ": ";
    cin >> anio;

    f.setDia(dia);
    f.setMes(mes);
    f.setAnio(anio);
}

// get

string Sprint::getNombre() 
{ 
  return string(_nombre);   
}  

bool Sprint::getActivo() 
{ 
  return _activo; 
}

int Sprint::getIdSprint()
{
    return _idSprint;
}

int Sprint::getIdProyecto()
{
    return _idProyecto;
}

int Sprint::getIdArea()
{
    return _idArea;
}

std::string Sprint::getStatus()
{
    return string(_status);
}

Fecha Sprint::getFechaInicio()
{
    return _fechaInicio;
}

Fecha Sprint::getFechaFin()
{
    return _fechaFin;
}

// Setters

void Sprint::setNombre(const std::string &nombre)
{
    strncpy(_nombre, nombre.c_str(), 50);
    _nombre[50] = '\0';
}

void Sprint::setIdSprint(int idSprint)
{
    _idSprint = idSprint;
}

void Sprint::setIdProyecto(int idProyecto)
{
    _idProyecto = idProyecto;
}

void Sprint::setIdArea(int idArea)
{
    _idArea = idArea;
}

void Sprint::setStatus(std::string status)
{
    strncpy(_status, status.c_str(), 19);
    _status[19] = '\0';
}

void Sprint::setFechaInicio(const Fecha &f)
{
    _fechaInicio = f;
}

void Sprint::setFechaFin(const Fecha &f)
{
    _fechaFin = f;
}

void Sprint::setFechaFinalizada()
{
    _fechaFinalizada = Fecha("finalizacion");
}

void Sprint::setActivo(bool activo){
    _activo = activo;
}
