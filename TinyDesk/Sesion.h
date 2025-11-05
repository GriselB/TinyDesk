//
//  Sesion.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 04/11/2025.
//

#pragma once

class Sesion {
private:
    int  _idUsuario;
    int  _idArea;
    int  _idRol;
    char _nombre[20];
    char _apellido[20];

public:
    Sesion();

    Sesion(int idUsuario, int idArea, int idRol, std::string nombre, std::string apellido);

    // Setters
    void setIdUsuario(int v);
    void setIdArea(int v);
    void setIdRol(int v);
    void setNombre(std::string v);
    void setApellido(std::string v);

    // Getters
    int  getIdUsuario();
    int  getIdArea();
    int  getIdRol();
    std::string getNombre();
    std::string getApellido();

    // Metodos
    void clear();

//    bool valida() { return _idUsuario > 0; }
};
