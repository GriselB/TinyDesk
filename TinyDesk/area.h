#pragma once
#include <string>

class Area 
{
  private:
    int _idArea;
    char _nombre[20];
  
  
  public:
    //getter
    int getIdArea();
    std::string getNombre();
    
    //setter
    void setIdArea(int idArea);
    void setNombreArea(std::string nombre);
    
    void seleccionar(); 
    void mostrarOpciones();
};
