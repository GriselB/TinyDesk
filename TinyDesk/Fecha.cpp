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
    setDia(dia);
    cout << "Ingrese mes de "<<nombre<<": ";
    cin >> mes;
    setMes(mes);
    cout << "Ingrese anio de "<<nombre<<": ";
    cin >> anio;
    setAnio(anio);
}

int Fecha::getDia()
{
  return _dia;
}

void Fecha::setDia(int dia)
{
    while(dia<0 || dia>31)
    {
        cout<<"Ingrese un dia entre 1 y 31: "<<endl;
        cin>>dia;
    }
    _dia = dia;
}

int Fecha::getMes()
{
  return _mes;
}

void Fecha::setMes(int mes)
{
    while(mes<0 || mes>13)
    {
        cout<<"Ingrese un mes entre 1 y 12: "<<endl;
        cin>>mes;
    }
        _mes = mes;
}

int Fecha::getAnio()
{
  return _anio;
}

void Fecha::setAnio(int anio)
{
    while(anio<1900)
    {
        cout<<"Ingrese un anio valido: "<<endl;
        cin>>anio;
    }
    _anio = anio;
}

string Fecha::toString()
{
  return to_string(_dia) + "/"+ to_string(_mes) + "/" + to_string(_anio);
}
