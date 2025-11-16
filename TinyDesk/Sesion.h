//
//  Sesion.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#pragma once
#include "area.h"

class Sesion {
private:
    int  _idUsuario;
    //int  _idArea;
    Area _area;
    int  _idRol;
    char _nombre[20];
    char _apellido[20];

public:
    Sesion();

    Sesion(int idUsuario, Area &area, int idRol, std::string nombre, std::string apellido);

    // Setters
    void setIdUsuario(int v);
    void setArea(Area &area);
    void setIdRol(int v);
    void setNombre(std::string v);
    void setApellido(std::string v);

    // Getters
    int  getIdUsuario();
    Area getArea();
    int  getIdRol();
    std::string getNombre();
    std::string getApellido();

    // Metodos
    void clear();
};
