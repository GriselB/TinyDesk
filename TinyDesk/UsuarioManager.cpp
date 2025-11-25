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

void UsuarioManager::cargarUsuario(Usuario &user) {

    string nombre, apellido, email, pass;
    int idRol, contadorChar;
    int caractMax;
    Area area;

    cleanBuffer();
    do{
        cout << "Nombre: ";
        cin>>nombre;
        const char *caracteres = nombre.c_str();
        contadorChar = 0;
        caractMax = 19;
        
        while (caracteres[contadorChar] != '\0') {
            contadorChar++;
            if(contadorChar > caractMax){
                cout << "El Nombre debe contener a lo sumo 19 caracteres." << endl;
                break;
            }
        }
    }while(contadorChar > 19);
    user.setNombre(nombre);
    
    cleanBuffer();
    do{
    cout << "Apellido: ";
    cin>>apellido;
        const char *caracteres = apellido.c_str();
        contadorChar = 0;
        caractMax = 19;
        
        while (caracteres[contadorChar] != '\0') {
            contadorChar++;
            if(contadorChar > caractMax){
                cout << "El Apellido debe contener a lo sumo 19 caracteres." << endl;
                break;
            }
        }
    }while(contadorChar > 19);
    user.setApellido(apellido);
    
    cleanBuffer();
    do{
        cout << "Email: ";
        cin>>email;
        const char *caracteres = email.c_str();
        contadorChar = 0;
        caractMax = 29;
        
        while (caracteres[contadorChar] != '\0') {
            contadorChar++;
            if(contadorChar > caractMax){
                cout << "El Email debe contener a lo sumo 29 caracteres." << endl;
                break;
            }
        }
    }while(contadorChar > 29);
    user.setEmail(email);
    
    cleanBuffer();
    do{
        cout << "Password: ";
        cin>>pass;
        const char *caracteres = pass.c_str();
        contadorChar = 0;
        caractMax = 49;
        
        while (caracteres[contadorChar] != '\0') {
            contadorChar++;
            if(contadorChar > caractMax){
                cout << "La contraseña debe contener a lo sumo 49 caracteres." << endl;
                break;
            }
        }
    }while(contadorChar > 49);
    user.setPassword(pass);
    
    cleanBuffer();
    do{
        cout << "ID de rol (1 para admin, 2 para empleado) : ";
        cin >> idRol;
    }while(idRol != 1 and idRol != 2);
    user.setIdRol(idRol);
    
    if(idRol==2){
        area.seleccionar();
        user.setArea(area);
    }
    if(idRol==1){
        area.setIdArea(1);
        area.setNombreArea("Administración");
        user.setArea(area);
    }

    user.setActivo(true);
}

void UsuarioManager::mostrarUsuario(Usuario &usuario) {
    const string ROLES[2] = {"Administrador", "Usuario"};
    
    cout<<"ID Usuario: "<<usuario.getIdUsuario()<<endl;
    cout<<"Nombre: "  <<usuario.getNombre()<<endl;
    cout<<"Apellido: "<<usuario.getApellido()<<endl;
    cout<<"Email: "<<usuario.getEmail()<<endl;
    cout<<"ID Rol: "<<usuario.getIdRol()<<endl;
    cout<<"Area: " << usuario.getArea().getNombreArea() <<endl;
    int idRol = usuario.getIdRol();
    cout<<"Rol: "<< ROLES[idRol-1] <<endl;
    cout<<"Activo: "<<(usuario.getActivo() ? "Sí" : "No") << "\n";
}

void UsuarioManager::crearUsuario() {
    Usuario user;
    user.setIdUsuario(_repo.getNuevoID());

    cout << "---- CREAR NUEVO USUARIO ----" << endl;

    cargarUsuario(user);

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
        mostrarUsuario(reg[i]);
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
                Sesion sesion;
                sesion.setIdUsuario(user.getIdUsuario());
                Area area = user.getArea();
                sesion.setArea(area);
                sesion.setIdRol(user.getIdRol());
                sesion.setNombre(user.getNombre());
                sesion.setApellido(user.getApellido());
                
                SesionArchivo sesArch;
                sesArch.guardar(sesion);
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

bool UsuarioManager::existeUsuario(int usuarioId){
    int pos = _repo.buscarID(usuarioId);
    if(pos<0) return false;
    
    Usuario user = _repo.leer(pos);
    
    if(user.getIdUsuario() == -1) return false;
    
    return user.getActivo();
}

bool UsuarioManager::verificarUsuarioArea(int usuarioId, int area){
    int pos = _repo.buscarID(usuarioId);
    if(pos<0) return false;
    
    Usuario user = _repo.leer(pos);
    
    if(user.getIdUsuario() == -1) return false;
    if(user.getArea().getIdArea() != area) return false;
    
    return true;
}

void UsuarioManager::eliminarUsuario(){
    int id, pos;
    Usuario usuario;
    UsuarioArchivo archivoUser;
    char eliminado;
    
    cout << "---- ELIMINAR USUARIO ----" << endl;
    cout << "Ingrese ID del Usuario a desactivar (0 para salir): ";
    cin >> id;

    if(id == 0){
        return;
    }
    pos = _repo.buscarID(id);
    
    if (pos < 0) {
        cout << "No existe un Usuario con ese ID." << endl;
        pause();
        return;
    }

    usuario = _repo.leer(pos);
    cout << "Informacion del Usuario: "<<endl;

    mostrarUsuario(usuario);
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
    
    pause();
}
