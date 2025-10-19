//
//  UsuarioManager.cpp
//  TinyDesk
//
//  Created by Sebastian Yanni on 18/10/2025.
//

#include <iostream>
#include "UsuarioManager.h"

using namespace std;

UsuarioManager::UsuarioManager() { }

void UsuarioManager::crearUsuario() {
    Usuario user;

    system("cls");

    cout << "---- CREAR NUEVO USUARIO ----" << endl;

    user.Cargar();

    if (existeEmail(user.getEmail())) {
        cout << "Error: ya existe un usuario con ese email." << endl;
        system("pause");
        return;
    }

    user.setIdUsuario(_repo.getNuevoID());
    user.setActivo(true);

    if (_repo.guardar(user)) {
        cout << "Usuario creado exitosamente."<<endl;
        cout << "ID: " << user.getIdUsuario() << endl;
        system("pause");
    } else {
        cout << "Error al guardar el usuario." << endl;
        system("pause");
    }
}

void UsuarioManager::mostrarUsuarios() {
    int cantReg = _repo.getCantidadRegistros();
    if (cantReg <= 0) {
        cout << "No hay usuarios." << endl;
        system("pause");
        return;
    }

    Usuario *reg = new Usuario[cantReg];
    if (reg == NULL) {
        cout << "Sin memoria. Hay unas baratas DDR5 en ML." << endl;
        system("pause");
        exit(-100);
        return;
    }

    _repo.leerTodos(reg, cantReg);

    system("cls");
    cout<<"                        ---- LISTA DE USUARIOS ----" << endl;
    for (int i = 0; i < cantReg; i++) {
        reg[i].Mostrar();
        cout << "--------------------------------" << endl;
    }
    system("pause");

    delete [] reg;
}

void UsuarioManager::iniciarSesion() {
    string email, pass;
    system("cls");
    cin.ignore();
    cout<<"                        ---- INICIO DE SESION ----" << endl;
    cout<<"Email: ";
    cin>>email;
    cout<<"Password: ";
    cin>>pass;

    int cantReg = _repo.getCantidadRegistros();
    for (int i = 0; i < cantReg; i++) {
        Usuario user = _repo.leer(i);
        if (user.getEmail()==email && user.getPassword()==pass && user.getActivo()) {
            cout << "Login OK."<<endl;
            cout << "Bienvenido, " << user.getNombre() << "!" << endl;
            system("pause");
            ///limpiar pantalla
            ///user.getIdRol() no, hay que usar la clase rol y ver el permiso, HAY QUE CAMBIARLO ES TEMPORAL.
            if(user.getIdRol() == 1){
                //mostramos pantalla para superAdmin.
                return;
            }else{
                //mostramos pantalla para empleado.
                return;
            }
        }
    }

    cout << "Credenciales invalidas o usuario inactivo." << endl;
    system("pause");
}

bool UsuarioManager::existeEmail(string email) {
    int cantReg = _repo.getCantidadRegistros();
    for (int i = 0; i < cantReg; i++) {
        Usuario user = _repo.leer(i);
        if (user.getEmail() == email) {
            return true;
        }
    }
    return false;
}
