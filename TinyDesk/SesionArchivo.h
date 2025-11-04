//
//  SesionArchivo.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#pragma once
#include "Sesion.h"

class SesionArchivo{
    
private:
    std::string _nombreArchivo = "SesionActual.dat";
    
public:
    bool guardar(Sesion &sesion);
    bool leer(Sesion &sesion);
    bool existeSesion();
    void cerrarSesion();
};
