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

/*void cleanBuffer() {
    int aux;
    while ((aux = std::cin.get()) != '\n' && aux != EOF) {}
}*/


void cleanBuffer() {
    int aux;
    while ((aux = std::cin.get()) != '\n' && aux != EOF) {}
}

void clear() {
    #ifdef _WIN64
        system("cls");
    #endif

    #ifdef __linux__
        system("clear");
    #endif

    #ifdef __APPLE__
        system("clear");
    #endif
}

void pause() {
    #ifdef _WIN64
        system("pause");
    #endif

    #ifdef __linux__
        int aux = 1;

        do{
            std::cout << "Ingresar 0 para continuar.\n";
            std::cin >> aux;
        } while (aux != 0);
    #endif

    #ifdef __APPLE__
        int aux = 1;
        std::cout << "\nIngresar 0 para continuar.\n";

        while (true) {
            if (std::cin >> aux && aux == 0) {
                break;
            } else {
                std::cin.clear();
                cleanBuffer();
                std::cout << "Ingresar 0 para continuar.\n";
            }
        }
    #endif
}

std::string evaluarCV(double cv){
    if (cv<=20) return std::string("rendimiento del usuario muy constante");
    if (cv<=30) return std::string("rendimiento del usuario bastante constante");
    if (cv<=40) return std::string("rendimiento del usuario variable");
    return std::string("rendimiento del usuario muy malo");
};
