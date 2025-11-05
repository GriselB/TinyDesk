#include <iostream>
#include "Fecha.h"
using namespace std;

Fecha::Fecha()
  : _dia(0), _mes(0), _anio(0)
{

}

Fecha::Fecha (int dia, int mes, int anio, bool b)
{
  setDia(dia,mes,b);
  setMes(mes);
  setAnio(anio);
}

Fecha::Fecha(std::string nombre)
{
    int dia,mes,anio;
    bool b;
    cout << "Ingrese anio de "<<nombre<<": ";
    cin >> anio;
    setAnio(anio);
    b=comprobarBisiesto(anio);
    cout << "Ingrese mes de "<<nombre<<": ";
    cin >> mes;
    setMes(mes);
    cout << "Ingrese dia de "<<nombre<<": ";
    cin >> dia;
    setDia(dia,mes,b);
}

int Fecha::getDia()
{
  return _dia;
}

void Fecha::setDia(int dia,int mes,bool b)
{
    int vMes[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (b)
    {
        while(dia>vMes[mes-1])
        {
            cout<<"Ingrese un dia valido para el mes "<<mes<<" en un anio bisiesto: "<<endl;
            cin>>dia;
        }
    }
    else
    {
        vMes[1]=28;
        while(dia>vMes[mes-1])
        {
            cout<<"Ingrese un dia valido para el mes "<<mes<<" en un anio no bisiesto: "<<endl;
            cin>>dia;
        }
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

bool Fecha::comprobarBisiesto(int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))
        return true;
    else
        return false;
}

string Fecha::toString()
{
  return to_string(_dia) + "/"+ to_string(_mes) + "/" + to_string(_anio);
}
