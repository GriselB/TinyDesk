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
    user.setIdUsuario(_repo.getNuevoID());

    cout << "---- CREAR NUEVO USUARIO ----" << endl;

    user.Cargar();

    if (existeEmail(user.getEmail())) {
        cout << "Error: ya existe un usuario con ese email." << endl;
        pause();
        return;
    }

    user.setActivo(true);

    if (_repo.guardar(user)) {
        cout << "Usuario creado exitosamente."<<endl;
        cout << "ID: " << user.getIdUsuario() << endl;
        pause();
        clear();
    } else {
        cout << "Error al guardar el usuario." << endl;
        pause();
        clear();
    }
}

void UsuarioManager::mostrarUsuarios() {
    int cantReg = _repo.getCantidadRegistros();
    if (cantReg <= 0) {
        cout << "No hay usuarios." << endl;
        pause();
        return;
    }

    Usuario *reg = new Usuario[cantReg];
    if (reg == NULL) {
        cout << "Sin memoria. Hay unas baratas DDR5 en ML." << endl;
        exit(-100);
        return;
    }

    _repo.leerTodos(reg, cantReg);

    cout<<"                        ---- LISTA DE USUARIOS ----" << endl;
    for (int i = 0; i < cantReg; i++) {
        reg[i].Mostrar();
        cout << "--------------------------------" << endl;
    }

    delete [] reg;
}

int UsuarioManager::iniciarSesion() {
    string email, pass;
    
    cin.ignore();
    cout<<"                        ---- INICIO DE SESION ----" << endl;
    cout<<"Email: ";
    cin>>email;
    cout<<"Password: ";
    cin>>pass;
    clear();
    
    int cantReg = _repo.getCantidadRegistros();
    for (int i = 0; i < cantReg; i++) {
        Usuario user = _repo.leer(i);
        
        if (user.getEmail()==email && user.getPassword()==pass && user.getActivo()) {
            cout << "Login OK."<<endl;
            cout << "------- Bienvenido, " << user.getNombre() << "!  -------" << endl;
            pause();
            
            int idRol = user.getIdRol();
            Rol rol = _rolRepo.leer(idRol - 1);
            if(rol.getIdRol() == -1){
                cout<<"Error al abrir el archivo Rol.dat"<<endl;
                return 0;
            }
            if(rol.getPermisosEscritura()){
                return 1;
            } else {
                return 2;
            }
        }
    }
    return 0;
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

void UsuarioManager::eliminarUsuario(){
    int id, pos;
    Usuario usuario;
    UsuarioArchivo archivoUser;
    char eliminado;
    
    cout << "---- ELIMINAR USUARIO ----" << endl;
    cout << "Ingrese ID del Usuario a desactivar: ";
    cin >> id;

    pos = _repo.buscarID(id);
    
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        system("pause");
        return;
    }

    usuario = _repo.leer(pos);
    cout << "Informacion del Sprint: "<<endl;

    usuario.Mostrar();
     cout << endl << "Quiere eliminarlo S/N:";
     cin >> eliminado;

    if(eliminado== 's' || eliminado == 'S')
    {        
      if(archivoUser.eliminar(pos))
      {
        cout << "El Usuario fue eliminado correctamente "<<endl;
      }
      else
      {
        cout << "Ocurrio un error en la eliminacion del Usuario"<<endl;
      }
    }
    
    system("pause");
}
