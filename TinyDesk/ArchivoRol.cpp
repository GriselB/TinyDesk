//
//  ArchivoRol.cpp
//  ROL - tp
//
//  Created by Sebastian Yanni on 23/10/2025.
//

#include <iostream>
#include "ArchivoRol.h"

ArchivoRol::ArchivoRol(std::string nombreArchivo) {
    _nombreArchivo = nombreArchivo;
}

bool ArchivoRol::grabar(Rol reg) {
    FILE* p = fopen(_nombreArchivo.c_str(), "ab");
    if (p == NULL) return false;
    bool ok = fwrite(&reg, sizeof(Rol), 1, p);
    fclose(p);
    return ok;
}

Rol ArchivoRol::leer(int pos) {
    Rol reg;
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return reg;
    fseek(p, sizeof(Rol) * pos, 0);
    fread(&reg, sizeof(Rol), 1, p);
    fclose(p);
    return reg;
}

int ArchivoRol::getCantidadRegistros() {
    FILE* p = fopen(_nombreArchivo.c_str(), "rb");
    if (p == NULL) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Rol);
}
