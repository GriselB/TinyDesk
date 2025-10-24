//
//  Usuario.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#include <iostream>
#include <cstring>
#include "Usuario.h"

using namespace std;

void Usuario::Cargar() {

    string nombre, apellido, email, pass;
    int idArea, idRol;

    cout << "Nombre: ";
    cin>>nombre;
    setNombre(nombre);

    cout << "Apellido: ";
    cin>>apellido;
    setApellido(apellido);

    cout << "Email: ";
    cin>>email;
    setEmail(email);

    cout << "Password: ";
    cin>>pass;
    setPassword(pass);

    do{
        cout << "ID de área: "<<endl;
        cout << "1: Administración"<<endl;
        cout << "2: Backend"<<endl;
        cout << "3: Frontend"<<endl;
        cout << "4: QA"<<endl;
        cout << "5: UX/UI"<<endl;
        cout << "ID área: ";
        cin >> idArea;
        setIdArea(idArea);
    }while(idArea < 1 or idArea > 5);

    do{
        cout << "ID de rol (1 para admin, 2 para empleado) : ";
        cin >> idRol;
    }while(idRol != 1 and idRol != 2);


    setActivo(true);
}

void Usuario::Mostrar() {
    cout<<"ID Usuario: "<<getIdUsuario()<<endl;
    cout<<"Nombre: "  <<getNombre()<<endl;
    cout<<"Apellido: "<<getApellido()<<endl;
    cout<<"Email: "<<getEmail()<<endl;
    cout<<"ID Área: "<<getIdArea()<<endl;
    cout<<"ID Rol: "<<getIdRol()<<endl;
    cout<<"Activo: "<<(getActivo() ? "Sí" : "No") << "\n";
}

string Usuario::getNombre() { return _nombre; }
string Usuario::getPassword() { return _password; }
string Usuario::getApellido() { return _apellido; }
string Usuario::getEmail() { return _email; }
int Usuario::getIdUsuario() { return _idUsuario; }
int Usuario::getIdArea() { return _idArea; }
int Usuario::getIdRol() { return _idRol; }
bool Usuario::getActivo() { return _activo; }

void Usuario::setNombre(std::string nombre) {
    strncpy(_nombre, nombre.c_str(), 19);
    _nombre[19] = '\0';
}

void Usuario::setPassword(std::string pass) {
    strncpy(_password, pass.c_str(), 49);
    _password[49] = '\0';
}

void Usuario::setApellido(string apellido) {
    strncpy(_apellido, apellido.c_str(), 19);
    _apellido[19] = '\0';
}

void Usuario::setEmail(string email) {
    strncpy(_email, email.c_str(), 29);
    _email[29] = '\0';
}

void Usuario::setIdUsuario(int idUsuario){
    _idUsuario = idUsuario;
}

void Usuario::setIdArea(int idArea){
    _idArea = idArea;
}

void Usuario::setIdRol(int idRol){
    _idRol = idRol;
}

void Usuario::setActivo(bool activo){
    _activo = activo;
}
