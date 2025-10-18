#include <iostream>
#include "utils.h"

std::string cargarCadena()
{
  std::string texto;

  if(std::cin.peek() == '\n')
  {
    std::cin.ignore();
  }

  std::getline(std::cin, texto);

  return texto;
}

int buscarMaximo(int vec[], int cant){
  int indexMax = 0;
  
  for(int i=1; i<cant; i++){
    if(vec[i] > vec[indexMax]){
      indexMax = i;    
    }  
  }
  
  return indexMax;
}
