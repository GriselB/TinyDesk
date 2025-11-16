//
//  SesionArchivo.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#include <iostream>
#include "SesionArchivo.h"

using namespace std;

bool SesionArchivo::guardar(Sesion &sesion) {
    FILE* file = fopen(_nombreArchivo.c_str(), "wb");
    if (file == nullptr) return false;
    bool ok = fwrite(&sesion, sizeof(Sesion), 1, file);
    fclose(file);
    return ok;
}

bool SesionArchivo::leer(Sesion &sesion) {
    FILE* file = fopen(_nombreArchivo.c_str(), "rb");
    if (file == nullptr) return false;
    bool ok = fread(&sesion, sizeof(Sesion), 1, file);
    fclose(file);
    return ok;
}

void SesionArchivo::cerrarSesion() {
    FILE* f = fopen(_nombreArchivo.c_str(), "wb");
    if (f) fclose(f);
}

bool SesionArchivo::existeSesion() {
    FILE* file = fopen(_nombreArchivo.c_str(), "rb");
    if (file == nullptr) return false;
    fclose(file);
    return true;
}
