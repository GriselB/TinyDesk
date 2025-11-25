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

// Función auxiliar: Convierte una fecha (D/M/A) a un número total de días
int Fecha::convertirAEntero() {
    // 1. Sumamos los días de los años completos anteriores
    int aniosCompletos = _anio - 1;
    int totalDias = aniosCompletos * 365;

    // 2. Sumamos los bisiestos acumulados en esos años
    // (Un año es bisiesto si es divisible por 4, excepto multiplos de 100, salvo multiplos de 400)
    totalDias += (aniosCompletos / 4) - (aniosCompletos / 100) + (aniosCompletos / 400);

    // 3. Sumamos los días de los meses completos del año actual
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Si el año actual es bisiesto, febrero tiene 29
    if (comprobarBisiesto(_anio)) { // Asumo que tienes este metodo o usa la logica de arriba
        diasPorMes[1] = 29;
    }

    // Sumamos los dias de los meses anteriores al actual
    for (int i = 0; i < _mes - 1; i++) {
        totalDias += diasPorMes[i];
    }

    // 4. Sumamos los días del mes actual
    totalDias += _dia;

    return totalDias;
}

// Función principal: Resta los dos números enteros
int Fecha::diferenciaEnDias(Fecha fechaComparar) {
    int misDias = this->convertirAEntero();
    int susDias = fechaComparar.convertirAEntero();
    
    // Retornamos la resta (puede dar negativo si la fechaComparar es anterior)
    return (int)(susDias - misDias);
}

