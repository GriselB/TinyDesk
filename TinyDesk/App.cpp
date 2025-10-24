#include <iostream>
#include "App.h"
using namespace std;

App::App(){
  _cantidadOpciones = 2;
}
void App::run(){
    int opcion;
    
    do{
        clear();
        opcion = seleccionOpcion();
        clear();
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
          
  case 1:{
      clear();
      int rol = _usuarioManager.iniciarSesion();

      if (rol == 1) {
          // ejecutar menú-admin
      }
      else if (rol == 2) {
          // ejecutar menú-empleado
      }
      else {
          cout << "Credenciales invalidas o usuario inactivo." << endl;
          pause();
          clear();
      }
      break;
    }
          
  case 2:
          clear();
          _usuarioManager.crearUsuario();
          break;
    
  case 0:
    cout << "Gracias por utilizar TinyDesk" << endl;
    break;
  }
}
