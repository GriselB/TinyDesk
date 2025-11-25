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
            cin.clear();
            cout<<"Ingrese un dia valido para el mes "<<mes<<" en un anio bisiesto: "<<endl;
            cin>>dia;
        }
    }
    else
    {
        vMes[1]=28;
        while(dia>vMes[mes-1])
        {
            cin.clear();
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

void Fecha::setMes(int &mes)
{
    while(mes<1 || mes>12)
    {
        cin.clear();
        cout<<"Ingrese un mes entre 1 y 12: "<<endl;
        cin>>mes;
    }
        _mes = mes;
}

int Fecha::getAnio()
{
  return _anio;
}

void Fecha::setAnio(int &anio)
{
    while(anio<2025 || anio >2050)
    {
        cin.clear();
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

//-------------------


int Fecha::convertirAEntero() {
    // Sumamos los días de los años completos menos el actual
    int aniosCompletos = _anio - 1;
    int totalDias = aniosCompletos * 365;

    // Sumamos los bisiestos
    totalDias += (aniosCompletos / 4) - (aniosCompletos / 100) + (aniosCompletos / 400);

    // Arrayd e dias por mes (año nomal)
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    

    if (comprobarBisiesto(_anio)) { 
        diasPorMes[1] = 29;
    }

    for (int i = 0; i < _mes - 1; i++) {
        totalDias += diasPorMes[i];
    }

    totalDias += _dia;

    return totalDias;
}


int Fecha::diferenciaEnDias(Fecha fechaComparar) {
    int misDias = this->convertirAEntero();
    int susDias = fechaComparar.convertirAEntero();

    return (int)(susDias - misDias);
}

