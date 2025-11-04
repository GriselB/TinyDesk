//
//  Sesion.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#include <iostream>
#include <cstring>
#include "Sesion.h"

using namespace std;

Sesion::Sesion(){
}

Sesion::Sesion(int idUsuario, int idArea, int idRol, string nombre, string apellido) {
    setIdUsuario(idUsuario);
    setIdArea(idArea);
    setIdRol(idRol);
    setNombre(nombre);
    setApellido(apellido);
}

// Setters
void Sesion::setIdUsuario(int v) { _idUsuario = v; }
void Sesion::setIdArea(int v)    { _idArea = v; }
void Sesion::setIdRol(int v)     { _idRol = v; }
void Sesion::setNombre(string v) {
    strncpy(_nombre, v.c_str(), 19);
    _nombre[19] = '\0';
}
void Sesion::setApellido(std::string v) {
    strncpy(_apellido, v.c_str(), 19);
    _nombre[19] = '\0';
}

// Getters
int  Sesion::getIdUsuario() { return _idUsuario; }
int  Sesion::getIdArea()    { return _idArea; }
int  Sesion::getIdRol()     { return _idRol; }
string Sesion::getNombre()   { return _nombre; }
string Sesion::getApellido() { return _apellido; }

// Metodos
void Sesion::clear() {
    _idUsuario = 0;
    _idArea = 0;
    _idRol = 0;
    _nombre[0] = '\0';
    _apellido[0] = '\0';
}
