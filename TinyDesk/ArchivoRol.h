//
//  ArchivoRol.h
//  ROL - tp
//
//  Created by Sebastian Yanni on 23/10/2025.
//

#pragma once
#include <string>
#include "Rol.h"

class ArchivoRol {
private:
    std::string _nombreArchivo;

public:
    ArchivoRol(std::string nombreArchivo = "Roles.dat");
    bool grabar(Rol reg);
    Rol leer(int pos);
    int getCantidadRegistros();
};

