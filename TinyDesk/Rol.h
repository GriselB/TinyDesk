//
//  Rol.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 23/10/2025.
//

#pragma once
#include <string>

class Rol {
private:
    int _idRol;
    char _nombreRol[20];
    bool _permisosEscritura;

public:
    void setIdRol(int id) { _idRol = id; }
    void setNombreRol(std::string nombre);
    void setPermisosEscritura(bool permiso) { _permisosEscritura = permiso; }

    int getIdRol() { return _idRol; }
    std::string getNombreRol() { return _nombreRol; }
    bool getPermisosEscritura() { return _permisosEscritura; }

    void mostrar() const;
};
