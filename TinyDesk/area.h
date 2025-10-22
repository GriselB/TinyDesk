#pragma once

class Area 
{
  private
    int _idArea;
    char _nombre[20];
  
  
  public
    int getIdArea();
    std::string getNombre();
    int setIdArea(int idArea);
    std::string setNombre(std::string nombre);
};
