#include <iostream>
#include "Fecha.h"
using namespace std;

Fecha::Fecha()
  : _dia(0), _mes(0), _anio(0)
{

}

Fecha::Fecha (int dia, int mes, int anio)
{
  setDia(dia);
  setMes(mes);
  setAnio(anio);
}

Fecha::Fecha(std::string nombre)
{
    int dia,mes,anio;
    cout << "Ingrese dia de "<<nombre<<": ";
    cin >> dia;
    cout << "Ingrese mes de "<<nombre<<": ";
    cin >> mes;
    cout << "Ingrese anio de "<<nombre<<": ";
    cin >> anio;
    setDia(dia);
    setMes(mes);
    setAnio(anio);
}

int Fecha::getDia()
{
  return _dia;
}

void Fecha::setDia(int dia)
{
    if(dia>0 && dia<31)
        _dia = dia;
}

int Fecha::getMes()
{
  return _mes;
}

void Fecha::setMes(int mes)
{
    if(mes>0 && mes<13)
        _mes = mes;
}

int Fecha::getAnio()
{
  return _anio;
}

void Fecha::setAnio(int anio)
{
    if(anio>1900)
        _anio = anio;
}

string Fecha::toString()
{
  return to_string(_dia) + "/"+ to_string(_mes) + "/" + to_string(_anio);
}
