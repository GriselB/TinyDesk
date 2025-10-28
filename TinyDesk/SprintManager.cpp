#include <iostream>
#include "SprintManager.h"
#include "Sprint.h"

using namespace std;

SprintManager::SprintManager() { }

void SprintManager::crearSprint() {

    system("cls");

    cout << "---- CREAR NUEVO SPRINT ----" << endl;
    Sprint sprint;
    sprint.Cargar();
    
    sprint.setIdSprint(_repo.getNuevoID());
    sprint.setStatus("Pendiente");  
    sprint.setActivo(true);

    
    

    if (_repo.guardar(sprint)) {
        cout << "Sprint guardado con éxito."<<endl;
        cout << "ID: " << sprint.getIdSprint() << endl;
        system("pause");
    } else {
        cout << "Error al guardar el sprint." << endl;
        system("pause");
    }
}


void SprintManager::listarSprints() {
    int cantReg = _repo.getCantidadRegistros();
    if (cantReg <= 0) {
        cout << "No hay sprints cargados." << endl;
        system("pause");
        return;
    }

    Sprint *reg = new Sprint[cantReg];
    if (reg == NULL) {
        cout << "Sin memoria." << endl;
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


void SprintManager::mostrarSprintPorID() {
    int id;
    cout << "Ingrese ID del Sprint: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un Sprint con ese ID." << endl;
        system("pause");
        return;
    }

    Sprint sprint = _repo.leer(pos);
    sprint.Mostrar();
    system("pause");
}

void SprintManager::finalizarSprint() {
    int id;
    cout << "ID del Sprint a finalizar: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un Sprint con ese ID." << endl;
        system("pause");
        return;
    }

    Sprint sprint = _repo.leer(pos);
    sprint.setStatus("Finalizado");
    sprint.setFechaFinalizada();

    FILE *pFile = fopen("sprints.dat", "rb+");
    if (pFile != nullptr) {
        fseek(pFile, sizeof(Sprint) * pos, SEEK_SET);
        fwrite(&sprint, sizeof(Sprint), 1, pFile);
        fclose(pFile);
        cout << "Sprint finalizado correctamente." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

    system("pause");
}

void SprintManager::eliminarSprintLogico() {
    int id;
    cout << "Ingrese ID del Sprint a desactivar: ";
    cin >> id;

    int pos = _repo.buscarID(id);
    if (pos < 0) {
        cout << "No existe un sprint con ese ID." << endl;
        system("pause");
        return;
    }

    Sprint sprint = _repo.leer(pos);
    sprint.setActivo(false);

    FILE *pFile = fopen("sprints.dat", "rb+");
    if (pFile != nullptr) {
        fseek(pFile, sizeof(Sprint) * pos, SEEK_SET);
        fwrite(&sprint, sizeof(Sprint), 1, pFile);
        fclose(pFile);
        cout << "Sprint desactivado." << endl;
    } else {
        cout << "No se pudo abrir el archivo." << endl;
    }

    system("pause");
}
