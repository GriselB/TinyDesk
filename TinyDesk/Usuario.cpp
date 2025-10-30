//
//  Usuario.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#include <iostream>
#include <cstring>
#include "Usuario.h"
#include "area.h"

using namespace std;

void Usuario::Cargar() {

    string nombre, apellido, email, pass;
    int idArea, idRol;
    Area area;
    
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

    area.seleccionar();
    

    do{
        cout << "ID de rol (1 para admin, 2 para empleado) : ";
        cin >> idRol;
    }while(idRol != 1 and idRol != 2);
    setIdRol(idRol);

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
