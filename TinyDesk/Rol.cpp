//
//  Rol.cpp
//  ROL - tp
//
//  Created by Sebastian Yanni on 23/10/2025.
//

#include <iostream>
#include <cstring>
#include "Rol.h"
using namespace std;

void Rol::setNombreRol(std::string nombre) {
    strncpy(_nombreRol, nombre.c_str(), 19);
    _nombreRol[19] = '\0';
}

void Rol::mostrar() const {
    cout << "ID Rol: " << _idRol << endl;
    cout << "Nombre: " << _nombreRol << endl;
    cout << "Permiso de escritura: " << (_permisosEscritura ? "Sí" : "No") << endl;
}
