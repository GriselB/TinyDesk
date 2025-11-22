#include <iostream>
#include "utils.h"

using namespace std;


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

bool fechaMenorOIgual(Fecha esMenor, Fecha esMayor) {
    if (esMenor.getAnio() > esMayor.getAnio()) return false;
    if (esMenor.getAnio() < esMayor.getAnio()) return true;

    if (esMenor.getMes() < esMayor.getMes()) return true;
    if (esMenor.getMes() > esMayor.getMes()) return false;

    if (esMenor.getDia() < esMayor.getDia()) return true;
    if (esMenor.getDia() > esMayor.getDia()) return false;

    return true;
}

std::string evaluarCV(double cv){
    if (cv<=20) return std::string("rendimiento muy constante");
    if (cv<=40) return std::string("rendimiento muy variable");
    return std::string("rendimiento muy malo");
}

void compararRendimientoUsuario(std::string titulo,
                                double diferenciaCumplimiento,
                                double diferenciaCumplimientoATiempo,
                                double cvUsuario,
                                double cvBase,
                                double cvUsuarioATiempo,
                                double cvBaseATiempo){
    
    cout << "--- Comparacion Usuario vs " << titulo << " ---" << endl;
    
    /// - CUMPLIMIENTO GENERAL -
    cout << "Cumplimiento general: ";
    if (diferenciaCumplimiento > 0) {
        cout << diferenciaCumplimiento << "% POR ENCIMA del promedio de " << titulo << "." << endl;
    }
    else if (diferenciaCumplimiento < 0) {
        cout << (diferenciaCumplimiento * -1) << "% POR DEBAJO del promedio de " << titulo << "." << endl;
    }
    else {
        cout << "igual al promedio de " << titulo << "." << endl;
    }
    
    /// - CONSISTENCIA EN CUMPLIMIENTO GENERAL -
    cout << "Consistencia del rendimiento: ";
    if (cvUsuario >= 0 && cvBase >= 0) {
        if (cvUsuario < cvBase) {
            cout << "el usuario es MAS ESTABLE que " << titulo << "." << endl;
        }
        else if (cvUsuario > cvBase) {
            cout << "el usuario es MAS INESTABLE que " << titulo << "." << endl;
        }
        else {
            cout << "el usuario tiene una estabilidad similar a " << titulo << "." << endl;
        }
    }
    else {
        cout << "no puede evaluarse (datos insuficientes)." << endl;
    }
    
    /// - CUMPLIMIENTO A TIEMPO -
    cout << "Cumplimiento A TIEMPO: ";
    if (diferenciaCumplimientoATiempo > 0) {
        cout << diferenciaCumplimientoATiempo
        << "% POR ENCIMA del promedio a tiempo de " << titulo << "." << endl;
    }
    else if (diferenciaCumplimientoATiempo < 0) {
        cout << (diferenciaCumplimientoATiempo * -1) << "% POR DEBAJO del promedio a tiempo de " << titulo << "." << endl;
    }
    else {
        cout << "igual al promedio a tiempo de " << titulo << "." << endl;
    }
    
    /// - CV A TIEMPO (consistencia) -
    cout << "Consistencia en puntualidad (entregas a tiempo): ";
    if (cvUsuarioATiempo >= 0 && cvBaseATiempo >= 0) {
        if (cvUsuarioATiempo < cvBaseATiempo) {
            cout << "el usuario es MAS ESTABLE en entregas a tiempo que " << titulo << "." << endl;
        }
        else if (cvUsuarioATiempo > cvBaseATiempo) {
            cout << "el usuario es MAS INESTABLE en entregas a tiempo que " << titulo << "." << endl;
        }
        else {
            cout << "el usuario tiene una estabilidad similar a " << titulo << " en entregas a tiempo." << endl;
        }
    }
    else {
        cout << "no puede evaluarse (insuficientes tickets finalizados a tiempo)." << endl;
    }
}
