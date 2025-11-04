#pragma once
#include <string>

class Fecha
{
  public:
    Fecha();
    Fecha (int dia, int mes, int anio, bool b);
    Fecha(std::string nombre);

    int getDia();
    void setDia(int dia,int mes,bool b);

    int getMes();
    void setMes(int mes);

    int getAnio();
    void setAnio(int anio);

    bool comprobarBisiesto(int anio);

    std::string toString(); // DD/MM/YYYY

  private:
    int _dia;
    int _mes;
    int _anio;
};
