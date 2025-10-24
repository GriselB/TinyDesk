#pragma once
#include <string>

class Fecha
{
  public:
    Fecha();
    Fecha (int dia, int mes, int anio);
    Fecha(std::string nombre);

    int getDia();
    void setDia(int dia);

    int getMes();
    void setMes(int mes);

    int getAnio();
    void setAnio(int anio);

    std::string toString(); // DD/MM/YYYY

  private:
    int _dia;
    int _mes;
    int _anio;
};
