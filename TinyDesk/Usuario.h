//
//  Usuario.h
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#pragma once
#include "Fecha.h"
#include "area.h"

class Usuario {
private:
    int   _idUsuario;
    char _nombre[20];
    char _password[50];
    char  _apellido[20];
    char  _email[30];
    int  _idArea;
    int   _idRol;
    bool  _activo;
    Area _area;
    
public:
    void Cargar();
    void Mostrar();
    
    //getters
    std::string getNombre();
    std::string getPassword();
    std::string getApellido();
    std::string getEmail();
    int  getIdUsuario();
    int  getIdArea();
    int  getIdRol();
    bool getActivo();
    
    //setters
    void setNombre(std::string nombre);
    void setPassword(std::string pass);
    void setApellido(std::string apellido);
    void setEmail(std::string email);
    void setIdUsuario(int idUsuario);
    void setIdArea(int idArea);
    void setIdRol(int idRol);
    void setActivo(bool activo);
};
