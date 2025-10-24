#pragma once
#include <string>

class Area 
{
  private:
    int _idArea;
    char _nombre[20];
  
  
  public:
    int getIdArea();
    std::string getNombre();
    void setIdArea(int idArea);
    void setNombre(std::string nombre);
};
