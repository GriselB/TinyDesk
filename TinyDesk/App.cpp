#include <iostream>
#include "App.h"
using namespace std;

App::App(){
  _cantidadOpciones = 2;
}
void App::run(){
  int opcion;
  
  do{
    system("cls");
    opcion = seleccionOpcion();
    system("cls");
    ejecutarOpcion(opcion);
  }while(opcion != 0);
}

void App::mostrarOpciones(){
    cout << "                      --- TINYDESK ---" << endl;
    cout << "1- INICIAR SESION "<<endl;
    cout << "2- CREAR CUENTA NUEVA "<<endl;
    cout << "-----------------" << endl;
    cout << "0- Salir "<<endl;
}

int App::seleccionOpcion(){
  int opcion;
  mostrarOpciones();
  cout << "---------------" << endl;
  cout << "Opcion: ";
  cin >> opcion;
  
  while(opcion < 0 || opcion > _cantidadOpciones){
    cout << "Opcion incorrecta..."<<endl;
    cout << "Opcion: ";
    cin >> opcion;
  }
  return opcion;
}

void App::ejecutarOpcion(int opcion){
  switch(opcion){
          
  case 1:
          _usuarioManager.iniciarSesion();
          break;
  break;
          
  case 2:
          _usuarioManager.crearUsuario();
          break;
    break;
    
  case 0:
    cout << "Gracias por utilizar TinyDesk" << endl;
    break;
  }
}
